#include <utility>

#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Frontend/CheckerRegistry.h"
using namespace clang;
using namespace ento;

namespace
{
  enum class AllocationStatus
  {
    None,
    Allocated,
    Deallocated
  };

  class AllocationStatusContext
  {
   private:
    AllocationStatus _status;

   public:
    AllocationStatusContext(AllocationStatus status) : _status(status)
    {
    }

    bool isAllocated() const
    {
      return _status == AllocationStatus::Allocated;
    }

    bool isDeallocated() const
    {
      return _status == AllocationStatus::Deallocated;
    }

    bool Deallocate()
    {
      if (_status == AllocationStatus::Deallocated)
      {
        return false;
      }
      else
      {
        _status = AllocationStatus::Deallocated;
        return true;
      }
    }

    bool Allocate()
    {
      if (_status == AllocationStatus::Allocated)
      {
        return false;
      }
      else
      {
        _status = AllocationStatus::Allocated;
        return true;
      }
    }

    // Needed if we are going to use generic maps
    // Used for a comparision of nodes
    bool operator==(const AllocationStatusContext &X) const
    {
      return _status == X._status;
    }

    // LLVM's equivalent of hash map
    // Passing bits of information to FoldintSetNodeID via Add_ methods
    // let us generate hash map values for each node
    void Profile(llvm::FoldingSetNodeID &ID) const
    {
      ID.AddInteger((int)_status);
    }
  };
}  // namespace

namespace
{
  class DeleteOperatorChecker : public Checker<
                                    check::PostStmt<CXXNewExpr>,
                                    check::PreStmt<CXXDeleteExpr>,
                                    check::PreCall,
                                    check::PreStmt<MemberExpr>,
                                    check::DeadSymbols>
  {
    mutable std::unique_ptr<BugType> deleteCalledMultiple;
    mutable std::unique_ptr<BugType> resourceLeak;
    mutable std::unique_ptr<BugType> deleteCalledOnNull;
    mutable std::unique_ptr<BugType> possibleDeleteCalledOnNull;
    mutable std::unique_ptr<BugType> useAfterDelete;

    void ReportMemoryLeakBug(std::vector<SymbolRef> symbols, CheckerContext &checkerContext) const;
    void ReportBug(CheckerContext &checkerContext, std::unique_ptr<BugType> &bugType, std::string message, bool sinkNode)
        const;

   public:
    DeleteOperatorChecker();

    void checkPreStmt(const CXXDeleteExpr *expr, CheckerContext &checkerContext) const;
    void checkPostStmt(const CXXNewExpr *expr, CheckerContext &checkerContext) const;
    void checkPreCall(const CallEvent &call, CheckerContext &checkerContext) const;
    void checkDeadSymbols(SymbolReaper &symbolReaper, CheckerContext &checkerContext) const;
    // Checks for the expressions such as x.y or x->y
    void checkPreStmt(const MemberExpr *expr, CheckerContext &checkerContext) const;
  };
}  // namespace

REGISTER_MAP_WITH_PROGRAMSTATE(AllocationMap, SymbolRef, AllocationStatusContext)

// Implementations

DeleteOperatorChecker::DeleteOperatorChecker()
{
  deleteCalledMultiple.reset(new BugType(this, "DeleteCalledMultipleTimes", "BugCategory"));
  resourceLeak.reset(new BugType(this, "ResourceLeak", "BugCategory"));
  deleteCalledOnNull.reset(new BugType(this, "DeleteCalledOnNull", "BugCategory"));
  possibleDeleteCalledOnNull.reset(new BugType(this, "PossibleDeleteCalledOnNull", "BugCategory"));
  useAfterDelete.reset(new BugType(this, "UseAfterDelete", "BugCategory"));
}

void DeleteOperatorChecker::checkPreStmt(const CXXDeleteExpr *expr, CheckerContext &checkerContext) const
{
  SVal argSVal = checkerContext.getSVal(expr->getArgument());

  SymbolRef argSymbol = argSVal.getAsSymbol();

  ProgramStateRef state = checkerContext.getState();

  // Nullability check
  ConditionTruthVal isNullCondition = state->isNull(argSVal);

  if (isNullCondition.isConstrainedTrue())
  {
    ReportBug(checkerContext, deleteCalledOnNull, "Delete called on a null.", true);
  }
  else if (isNullCondition.isUnderconstrained())
  {
    // Reports warning when no nullability checks are done in code
    ReportBug(checkerContext, possibleDeleteCalledOnNull, "There's possibility of calling delete on a null.", false);
  }

  const AllocationStatusContext *asc = state->get<AllocationMap>(argSymbol);

  // It means we ran into delete statement on a memory location that isn't
  // allocated (atleast not in the current scope/file?)
  if (asc == NULL)
  {
    return;
  }

  if (asc->isDeallocated())
  {
    ReportBug(checkerContext, deleteCalledMultiple, "Delete called multiple times on the same memory location.", true);
  }

  // Set status of our argument symbol to deallocated and add thetransition to
  // the next state
  state = state->set<AllocationMap>(argSymbol, AllocationStatusContext(AllocationStatus::Deallocated));
  checkerContext.addTransition(state);
}

void DeleteOperatorChecker::checkPostStmt(const CXXNewExpr *expr, CheckerContext &checkerContext) const
{
  ProgramStateRef state = checkerContext.getState();

  SVal retVal = checkerContext.getSVal(expr);

  // Try to convert the symbolic value to value of a location (pointer value)
  if (!retVal.getAs<Loc>())
    return;

  SymbolRef symbol = retVal.getAsLocSymbol();

  state = state->set<AllocationMap>(symbol, AllocationStatusContext(AllocationStatus::Allocated));
  checkerContext.addTransition(state);
}

// Checks if instance methods are called on deallocated object
void DeleteOperatorChecker::checkPreCall(const CallEvent &call, CheckerContext &checkerContext) const
{
  // Try to get the callee of a method
  const CXXInstanceCall *callee = dyn_cast<CXXInstanceCall>(&call);

  if (!callee)
  {
    return;
  }

  // Get *this pointer as SVal and convert it to a symbol
  SymbolRef symbol = callee->getCXXThisVal().getAsSymbol();

  ProgramStateRef state = checkerContext.getState();
  const AllocationStatusContext *asc = state->get<AllocationMap>(symbol);

  if (asc != nullptr && asc->isDeallocated())
  {
    ReportBug(checkerContext, useAfterDelete, "Object used after delete.", true);
  }
}

// Check if we've left scope without deallocating memory
void DeleteOperatorChecker::checkDeadSymbols(SymbolReaper &symReaper, CheckerContext &checkerContext) const
{
  ProgramStateRef state = checkerContext.getState();

  std::vector<SymbolRef> leakedMemorySymbols;

  AllocationMapTy mapValues = state->get<AllocationMap>();

  for (auto i = mapValues.begin(), end = mapValues.end(); i != end; ++i)
  {
    // Iterating through map values actually returns tuple
    // in form of (SymbolRef, AllocationStatusContext)
    SymbolRef symbol = i->first;

    bool butDidYouDie = symReaper.isDead(symbol);

    // We want to check if SValue is null
    // If it is, then we shouldn't report memory leak bug
    // since memory isn't allocated successfully there's no need to deallocate
    // If it is Unknown, generate warning about possibility of a memory leak
    ConstraintManager &manager = state->getConstraintManager();
    ConditionTruthVal isNullCondition = manager.isNull(state, symbol);

    if (butDidYouDie && !i->second.isDeallocated() && isNullCondition.isConstrainedFalse())
    {
      leakedMemorySymbols.push_back(symbol);
    }

    // If symbol is reaped, no need to keep it in dictionary
    if (butDidYouDie)
    {
      state = state->remove<AllocationMap>(symbol);
    }
  }

  if (leakedMemorySymbols.size() > 0)
  {
    ReportMemoryLeakBug(leakedMemorySymbols, checkerContext);
  }
}

// Triggered upon member access of an object
void DeleteOperatorChecker::checkPreStmt(const MemberExpr *expr, CheckerContext &checkerContext) const
{
  // Get instance containing accessed field
  SVal val = checkerContext.getSVal(expr->getBase());

  SymbolRef symbol = val.getAsSymbol();

  ProgramStateRef state = checkerContext.getState();
  const AllocationStatusContext *asc = state->get<AllocationMap>(symbol);

  if (asc != nullptr && asc->isDeallocated())
  {
    ReportBug(checkerContext, useAfterDelete, "Object used after delete.", true);
  }
}

void DeleteOperatorChecker::ReportBug(
    CheckerContext &checkerContext,
    std::unique_ptr<BugType> &bugType,
    std::string message,
    bool sinkNode) const
{
  ExplodedNode *errorNode = sinkNode ? checkerContext.generateErrorNode() : checkerContext.generateNonFatalErrorNode();

  if (!errorNode)
  {
    return;
  }

  auto bugReport = std::make_unique<PathSensitiveBugReport>(*bugType, message, errorNode);

  checkerContext.emitReport(std::move(bugReport));
}

void DeleteOperatorChecker::ReportMemoryLeakBug(std::vector<SymbolRef> symbols, CheckerContext &checkerContext) const
{
  // TODO: Report a bug or a warning for each symbol in the vector

  ExplodedNode *errorNode = checkerContext.generateNonFatalErrorNode();

  if (!errorNode)
  {
    return;
  }

  auto bugReport =
      std::make_unique<PathSensitiveBugReport>(*resourceLeak, "You haven't released allocated memory.", errorNode);

  checkerContext.emitReport(std::move(bugReport));
}

// Register plugin!
extern "C" void clang_registerCheckers(CheckerRegistry &registry)
{
  registry.addChecker<DeleteOperatorChecker>(
      "ANA.DeleteOperatorChecker",
      "Simple checker that triggers some basic sanity checks when using <i> new </i> and <i> delete </i> operators.",
      "");
}

extern "C" const char clang_analyzerAPIVersionString[] = CLANG_ANALYZER_API_VERSION_STRING;
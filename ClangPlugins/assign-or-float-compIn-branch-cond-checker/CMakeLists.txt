set(LLVM_LINK_COMPONENTS
  Support
  )

set(LLVM_EXPORTED_SYMBOL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/AssignOrFloatCompInBranchCondChecker.exports)
add_llvm_library(ANA_AssignOrFloatCompInBranchCondChecker MODULE BUILDTREE_ONLY AssignOrFloatCompInBranchCondChecker.cpp)

target_link_libraries(ANA_AssignOrFloatCompInBranchCondChecker PRIVATE
  clangAnalysis
  clangAST
  clangStaticAnalyzerCore
  clangStaticAnalyzerFrontend
  )

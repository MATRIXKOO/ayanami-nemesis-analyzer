// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s
class A
{
};

void test_2_helper(A* obj)
{
  if (obj != nullptr)
  {
    delete obj;
  }
}

void test_2()
{
  A* obj = nullptr;

  test_2_helper(obj);  // Shouldn't generate warning
}

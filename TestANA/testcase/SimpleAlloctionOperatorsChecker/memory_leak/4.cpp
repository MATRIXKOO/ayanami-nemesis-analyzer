// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1
class A
{
};

void test_4_helper(A* obj)
{
  delete obj;
}

void test_4()
{
  test_4_helper(new A());  // This shouldn't generate warning
}

// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s
class A
{
};

void test_4_helper(A* obj)
{
  delete obj;
}

void test_4()
{
  A* obj = new A();

  test_4_helper(obj);  // This shouldn't generate warning
}

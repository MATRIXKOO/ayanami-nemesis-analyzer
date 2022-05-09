// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s
class A
{
};

A* test_5_helper()
{
  return new A();
}

void test_5()
{
  A* obj = new A();
  delete obj;

  obj = test_5_helper();
  delete obj;  // This shouldn't generate warning
}

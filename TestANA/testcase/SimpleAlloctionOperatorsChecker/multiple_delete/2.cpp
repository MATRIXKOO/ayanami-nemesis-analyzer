// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s
class A
{
};

void test_2()
{
  A* obj = new A();
  delete obj;

  obj = new A();
  delete obj;  // This shouldn't generate warning
}

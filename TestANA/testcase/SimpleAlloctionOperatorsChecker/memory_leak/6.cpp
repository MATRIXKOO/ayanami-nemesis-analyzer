// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1
class A
{
};

void test_6()
{
  if (0)
  {
    A* obj = new A();  // This shouldn't generate warning
  }
}

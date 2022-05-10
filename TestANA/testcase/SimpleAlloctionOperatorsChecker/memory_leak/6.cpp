// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1 | FileCheck %s
//  CHECK-LABEL:   warning: You haven't released allocated memory [ANA.DeleteOperatorChecker]
class A
{
};

void test_6()
{
  A* obj = new A();
  bool condition = &test_6;  // get a unknown boolean
  if (!condition)
  {
    delete obj;
  }
  else
  {
    // no delete at all
  }
}
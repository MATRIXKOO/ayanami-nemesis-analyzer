// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1 | FileCheck %s
//  CHECK-LABEL:   warning: You haven't released allocated memory [ANA.DeleteOperatorChecker]
class A
{
};

void test_2()
{
  A* obj = new A();
  delete obj;

  obj = new A();  // This should generate warning : "You haven't released allocated memory."
}

// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1 | FileCheck %s
//  CHECK-LABEL:   warning: "Delete called multiple times on the same memory location.
class A
{
};

void test_1()
{
  A* obj = new A();
  delete obj;

  delete obj;  // This should generate warning: "Delete called multiple times on the same memory location."
}

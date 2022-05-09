// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1 | FileCheck %s
//  CHECK-LABEL:  warning: Delete called multiple times on the same memory location [ANA.DeleteOperatorChecker]
class A
{
};

void test_3_helper(A* obj)
{
  delete obj;
}

void test_3()
{
  A* obj = new A();
  delete obj;

  test_3_helper(obj);  // This should generate warning: "Delete called multiple times on the same memory location."
}

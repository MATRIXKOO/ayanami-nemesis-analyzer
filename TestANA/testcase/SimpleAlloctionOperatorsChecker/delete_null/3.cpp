// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1 | FileCheck %s
//  CHECK-LABEL:   warning: Delete called on a null [ANA.DeleteOperatorChecker]
class A
{
};

void test_3_helper(A* obj)
{
  if (obj == nullptr)
  {
    delete obj;
  }
}

void test_3()
{
  A* obj = nullptr;

  test_3_helper(obj);  // Should generate warning "Delete called on a null."
}

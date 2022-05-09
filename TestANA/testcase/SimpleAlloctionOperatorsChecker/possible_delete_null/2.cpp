// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1 | FileCheck %s
//  CHECK-LABEL:   warning: "There's possibility of calling delete on a null."
class A
{
};

void test_2(A* obj, bool someCondition)
{
  if (someCondition)
  {
    delete obj;  // Should generate warning: "There's possibility of calling delete on a null."
  }
}

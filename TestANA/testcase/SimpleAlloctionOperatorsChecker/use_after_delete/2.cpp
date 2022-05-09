// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_SimpleAllocationOperatorsChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
// RUN: %s 2>&1 | FileCheck %s
//  CHECK-LABEL:   warning: "Object used after delete."
class A
{
 public:
  int field = 42;
  void someFunction()
  {
  }
};

void test_2()
{
  A* obj = new A();
  delete obj;

  obj->someFunction();  // This should generate warning: "Object used after delete."
}

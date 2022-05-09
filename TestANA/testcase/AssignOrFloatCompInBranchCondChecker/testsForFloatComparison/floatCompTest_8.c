float f()
{
  float x = 1.3f;
  return x;
}
// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s 2>&1 | FileCheck %s
// CHECK-LABEL:   warning: Comparison of float values in branch condition can cause undefined behavior due to impreciseness
// of float comparison [ANA.AssignOrFloatCompInBranchCondChecker]
void test()
{
  float x = 0.1f;
  do
  {
    x++;
  } while (x <= f());  // expected warning for float loop counter
}

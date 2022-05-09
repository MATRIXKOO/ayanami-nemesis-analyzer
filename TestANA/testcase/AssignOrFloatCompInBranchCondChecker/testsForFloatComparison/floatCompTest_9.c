// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s 2>&1 | FileCheck %s
// CHECK-LABEL:   warning: Comparison of float values in branch condition can cause undefined behavior due to impreciseness
// of float comparison [ANA.AssignOrFloatCompInBranchCondChecker]
void test()
{
  float x = 0.1f;
  float y = 3.4f;
  if (x <= y)
    return;  // expected warning for float comparison
}

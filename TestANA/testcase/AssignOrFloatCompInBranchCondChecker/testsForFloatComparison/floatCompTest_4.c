// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s 2>&1 | FileCheck %s
// CHECK-LABEL:   warning: Comparison of float values in branch condition can cause undefined behavior due to impreciseness
// of float comparison [ANA.AssignOrFloatCompInBranchCondChecker]
void test()
{
  float y = 4.5;

  for (float x = 0.1f; x <= y; x++)  // expected warning for float loop counter
    break;
}

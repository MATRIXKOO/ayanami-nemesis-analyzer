// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s 2>&1 | FileCheck %s
// CHECK-LABEL: warning: Controlling operand in condition statement is assignment [ANA.AssignOrFloatCompInBranchCondChecker]
void test()
{
  float x = 0.1;

  if (x < 3, x = (2 > 3))  // expected warning for assign in controlling stmt
    return;
}

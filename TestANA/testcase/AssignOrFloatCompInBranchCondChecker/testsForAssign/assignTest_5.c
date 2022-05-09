// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s 2>&1 | FileCheck %s
// CHECK-LABEL: warning: Controlling operand in condition statement is assignment [ANA.AssignOrFloatCompInBranchCondChecker]
void test()
{
  int x = 1, y = 2, z = 3;

  if (x == 2, (y && x), z, z = 3)  // expected warning for assign in controlling stmt
    return;
}

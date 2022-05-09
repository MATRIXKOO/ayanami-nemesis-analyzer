// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s 2>&1 | FileCheck %s
// CHECK-LABEL: warning: Controlling operand in condition statement is assignment [ANA.AssignOrFloatCompInBranchCondChecker]

void test()
{
  int x = 1, y = 2, z = 3, w = 4;

  while (x = 1, y = (w - z), y, z = 5)  // expected warning for assign in controlling stmt
    break;
}

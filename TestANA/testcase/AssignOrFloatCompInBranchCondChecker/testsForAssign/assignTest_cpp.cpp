// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s
// CHECK-LABEL: warning: Controlling operand in condition statement is assignment [ANA.AssignOrFloatCompInBranchCondChecker]
void test()
{
  int x = 2, y = 3;

  do
  {
  } while ((x = 1) == (y = 1), y = 1, y = 2);  // expected warning for assign in controlling stmt
}
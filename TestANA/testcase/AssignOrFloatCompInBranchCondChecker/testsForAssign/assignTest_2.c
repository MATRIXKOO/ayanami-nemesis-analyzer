// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s
void test()
{
  int x = 2, y = 3;
  do
  {
  } while ((x = 1) == (y = 1), y = 1, y);  // no warning expected
}

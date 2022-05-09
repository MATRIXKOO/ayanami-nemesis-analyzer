// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s
void test()
{
  float x = 12, y = 0.12;

  while (x > (x * y - 0.1))  // no warning expected
    break;
}

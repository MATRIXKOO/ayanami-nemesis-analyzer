// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s

void test()
{
  int x = 1, y = 2, z = 3;

  if (x = 3, y = 3, y = 4, z)  // no warning expected
    return;
}

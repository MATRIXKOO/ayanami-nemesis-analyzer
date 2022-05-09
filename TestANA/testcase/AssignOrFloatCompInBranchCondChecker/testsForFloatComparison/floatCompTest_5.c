// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
// RUN: -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker\
// RUN: %s

void test()
{
  float x;

  for (x = 0.1f; x < 4; x += 0.1f)  // no warning expected
    break;
}

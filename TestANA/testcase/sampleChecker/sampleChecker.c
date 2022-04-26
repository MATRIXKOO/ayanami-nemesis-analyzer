// RUN: %ClangPath/clang -cc1 -load  %PluginPath/ANATestPlugin.dylib \
// RUN: -analyze -analyzer-checker=example.MainCallChecker\
// RUN: %s
// run test to see if the checker works
int main();

void caller()
{
  main();  // expected-warning {{call to main}}
}
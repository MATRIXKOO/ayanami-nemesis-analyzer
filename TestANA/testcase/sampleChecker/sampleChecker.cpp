// RUN: %ClangPath/clang++ -cc1 -load  %PluginPath/ANATestPlugin.dylib \
// RUN: -analyze -analyzer-checker=example.MainCallChecker\
// RUN: %s 2>&1 | FileCheck %s
// CHECK-LABEL: warning: call to main [example.MainCallChecker]
// run test to see if the checker works
int main();

void caller()
{
  main();  // expected-warning {{call to main}}
}
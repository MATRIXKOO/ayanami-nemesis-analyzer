 /Volumes/CODE/llvm-project/build/bin/clang++ -cc1 -load build/lib/clang-plugin/ANATestPlugin.dylib \
 -analyze -analyzer-checker=example.MainCallChecker \
TestANA/testcase/sampleChecker/sampleChecker.cpp
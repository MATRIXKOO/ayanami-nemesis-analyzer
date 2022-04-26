 /Volumes/CODE/llvm-project/build/bin/clang-15 -cc1 -load build/lib/clang-plugins/sample-checker/ANATestPlugin.dylib \
-analyze -analyzer-checker=example.MainCallChecker \
TestANA/testcase/sampleChecker/sampleChecker.c
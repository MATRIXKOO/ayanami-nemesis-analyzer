 /Volumes/CODE/llvm-project/build/bin/clang-15 -cc1 -load build/ClangPlugins/assign-or-float-compin-branch-cond-checker/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
-analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker \
TestANA/testcase/AssignOrFloatCompInBranchCondChecker/testsForFloatComparison/floatCompTest_1.c


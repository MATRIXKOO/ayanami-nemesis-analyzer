 /Volumes/CODE/llvm-project/build/bin/clang++ -cc1 -load build/lib/clang-plugin/ANA_AssignOrFloatCompInBranchCondChecker.dylib \
 -analyze -analyzer-checker=ANA.AssignOrFloatCompInBranchCondChecker \
TestANA/testcase/AssignOrFloatCompInBranchCondChecker/testsForFloatComparison/floatCompTest_cpp.cpp
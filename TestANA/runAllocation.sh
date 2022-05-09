 /Volumes/CODE/llvm-project/build/bin/clang++ -cc1 -load build/lib/clang-plugin/ANA_SimpleAllocationOperatorsChecker.dylib \
 -analyze -analyzer-checker=ANA.DeleteOperatorChecker \
TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/1.cpp
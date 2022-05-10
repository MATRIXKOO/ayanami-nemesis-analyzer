# RUN: sh @file
/Volumes/CODE/llvm-project/build/bin/clang++ -cc1  \
-load build/lib/clang-plugin/ANA_SimpleAllocationOperatorsChecker.dylib \
-analyze \
-analyzer-checker=ANA.DeleteOperatorChecker TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/6.cpp \
 -o build/report

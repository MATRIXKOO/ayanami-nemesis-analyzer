export clang_cc="/Volumes/CODE/llvm-project/build/bin/clang++ -cc1"  
export clang_plugin="-load build/lib/clang-plugin"
export clang_plugin_test_path="TestANA/testcase"

# run sampleChecker
export checker="-analyzer-checker=example.MainCallChecker"
export checkerName=$clang_plugin/ANATestPlugin.dylib
$clang_cc $checkerName \
-analyze \
$checker \
$clang_plugin_test_path/sampleChecker/sampleChecker.c -o build/report/sampleChecker

# run float
export checker="-analyzer-checker=example.MainCallChecker"
export checkerName=$clang_plugin/ANATestPlugin.dylib
$clang_cc $checkerName \
-analyze \
$checker \
$clang_plugin_test_path/AssignOrFloatCompInBranchCondChecker/testsForFloatComparison/floatCompTest_cpp.cpp\
-o build/report/floatCompTest

# run memory
export checker="-analyzer-checker=example.MainCallChecker"
export checkerName=$clang_plugin/ANA_SimpleAllocationOperatorsChecker.dylib
export memoryCheck=$clang_cc $checkerName \
-analyze \
$clang_plugin_test_path/SimpleAlloctionOperatorsChecker/
fd . 'build/report' -e html
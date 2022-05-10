hyperfine '/Volumes/CODE/llvm-project/build/bin/clang++ -cc1 -load build/lib/clang-plugin/ANA_SimpleAllocationOperatorsChecker.dylib \
 -analyze -analyzer-checker=ANA.DeleteOperatorChecker TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/1.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/2.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/3.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/4.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/1.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/2.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/3.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/4.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/5.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/6.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/1.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/2.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/3.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/4.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/5.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/possible_delete_null/1.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/possible_delete_null/2.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/use_after_delete/1.cpp \
TestANA/testcase/SimpleAlloctionOperatorsChecker/use_after_delete/2.cpp '

# 14 warnings in total. usrtime: 20ms


hyperfine 'fd . 'TestANA/testcase' -e c -e cpp -j 10 --exec cppcheck'

# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/1.cpp ...
# 1/19 files checked 4% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/2.cpp ...
# 2/19 files checked 9% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/3.cpp ...
# 3/19 files checked 15% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/delete_null/4.cpp ...
# 4/19 files checked 20% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/1.cpp ...
# TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/1.cpp:12:1: error: Memory leak: obj [memleak]
# }
# ^
# 5/19 files checked 26% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/2.cpp ...
# TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/2.cpp:15:1: error: Memory leak: obj [memleak]
# }
# ^
# 6/19 files checked 31% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/3.cpp ...
# 7/19 files checked 36% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/4.cpp ...
# 8/19 files checked 40% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/5.cpp ...
# 9/19 files checked 46% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/memory_leak/6.cpp ...
# 10/19 files checked 52% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/1.cpp ...
# TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/1.cpp:14:10: error: Memory pointed to by 'obj' is freed twice. [doubleFree]
#   delete obj;  // This should generate warning: "Delete called multiple times on the same memory location."
#          ^
# TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/1.cpp:12:3: note: Memory pointed to by 'obj' is freed twice.
#   delete obj;
#   ^
# TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/1.cpp:14:10: note: Memory pointed to by 'obj' is freed twice.
#   delete obj;  // This should generate warning: "Delete called multiple times on the same memory location."
#          ^
# 11/19 files checked 58% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/2.cpp ...
# 12/19 files checked 62% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/3.cpp ...
# 13/19 files checked 68% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/4.cpp ...
# 14/19 files checked 73% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/multiple_delete/5.cpp ...
# 15/19 files checked 77% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/possible_delete_null/1.cpp ...
# 16/19 files checked 82% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/possible_delete_null/2.cpp ...
# 17/19 files checked 88% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/use_after_delete/1.cpp ...
# TestANA/testcase/SimpleAlloctionOperatorsChecker/use_after_delete/1.cpp:19:12: error: Dereferencing 'obj' after it is deallocated / released [deallocuse]
#   int ft = obj->field;  // This should generate warning: "Object used after delete."
#            ^
# 18/19 files checked 94% done
# Checking TestANA/testcase/SimpleAlloctionOperatorsChecker/use_after_delete/2.cpp ...
# 19/19 files checked 100% done
# 4: error 2:note realtime: 50ms




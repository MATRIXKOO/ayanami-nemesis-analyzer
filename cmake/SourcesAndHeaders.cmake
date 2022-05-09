set(sources
   src/tmp.cpp
)

set(exe_sources
		src/main.cpp
)

set(headers
    include/borrow_checker/borrow_checker.hpp
    include/borrow_checker/borrow.hpp
)

set(test_sources
  src/tmp_test.cpp # the templated test
  src/borrow_checker_test.cpp
  src/borrow_test.cpp
)

set(clang_plugins_sources
  src/clang_plugins/PrintFunctionsAction.cpp  
)

echo "run clang plugin tests"
lit TestANA/testcase/
echo "run ANA lib tests"
echo "you must install fd ( https://github.com/sharkdp/fd )"
./build/test/borrow_checker_test_Tests
./build/test/borrow_test_Tests

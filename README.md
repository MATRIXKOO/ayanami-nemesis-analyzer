[![Actions Status](https://github.com/MATRIXKOO/ayanami-nemesis-analyzer/workflows/MacOS/badge.svg)](https://github.com/MATRIXKOO/ayanami-nemesis-analyzer/actions)
[![Actions Status](https://github.com/MATRIXKOO/ayanami-nemesis-analyzer/workflows/Windows/badge.svg)](https://github.com/MATRIXKOO/ayanami-nemesis-analyzer/actions)
[![Actions Status](https://github.com/MATRIXKOO/ayanami-nemesis-analyzer/workflows/Ubuntu/badge.svg)](https://github.com/MATRIXKOO/ayanami-nemesis-analyzer/actions)
[![codecov](https://codecov.io/gh/MATRIXKOO/ayanami-nemesis-analyzer/branch/master/graph/badge.svg)](https://codecov.io/gh/MATRIXKOO/ayanami-nemesis-analyzer)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/MATRIXKOO/ayanami-nemesis-analyzer)](https://github.com/MATRIXKOO/ayanami-nemesis-analyzer/releases)

# Ayanami Nemesis Analyzer

ANAlyzer is a analyze tool that can be used to analyze the CPP memory leaks (or more?). And checks collections. Including fews Concepts librarys which used C++20.
Now It is based on Clang Static Analyzer, I want to make it as a static analyzer that can be used analyze languages which gereated their codes to LLVM IR.
And I will implement some features that can be used to analyze the language.(all algorithms in static analysis of or program analysis)

For a long time, how to quickly find loopholes and find various potential errors in programs as far as possible has been an important issue in the computer science community. This issue has also been highly valued by large international software companies. In industry, people often use different detection methods to find bugs in software and improve the quality of software. Different from the dynamic testing method, we can also directly analyze the program code without running the software and find some errors. This kind of method is called static analysis. It is an important research direction in the field of programming language and compilation and software engineering. A relatively well-known early-developed static analysis tool is lint, which mainly checks for security issues in the C language. In recent years, static analysis technology has gradually attracted the attention of scholars in the fields of operating systems and information security. Some core semantics proposed by the Rust language can also as a reference to other languages. This paper focuses on the security enhancement of C++ and uses static analysis technology to analyze the memory problems of C++. The harm caused by the vulnerability, etc., for pointers and other problems, the corresponding solutions are given, and a borrow check library similar to Rust is provided for developers. Several checks are implemented based on the Clang Static Analyzer, which has advantages over existing static analysis tools.

# useage

download my release but remember to use llvm@15 or higher.
and run the command.

```bash
 /path/to/install/clang++ -cc1 -load ANA.dylib \
 -analyze -analyzer-checker=ANA \
foobar.cpp
```

# building

## dependencies

you can make your own dependencys conan or vcpkg
{fmt} and google , or use the git submodule
use llvm@15 or higher

## build

first, you need to install all dependencies.
and then, you can build.

```bash
mkdir build
cd build
cmake .. -G Ninja # optional  obviously
ninja
```

we get the following targets.
ClangPlugins
├── assign-or-float-compIn-branch-cond-checker
├── CMakeLists.txt
├── function-printer
├── sample-checker
└── simple-allocation-operators-checker

build the analyzer. you want to.

## test

just simple see the example in the Test directory.
./runALLtest.sh

## benchmark

### Dependency

install the following dependencies.
fd -- you must install fd ( <https://github.com/sharkdp/fd> ) first

and run the benchmark in the utils

set(LLVM_LINK_COMPONENTS
  Support
  )

set(LLVM_EXPORTED_SYMBOL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/SimpleAllocationOperatorsChecker.exports)
add_llvm_library(ANA_SimpleAllocationOperatorsChecker MODULE BUILDTREE_ONLY DeleteOperatorChecker.cpp)

target_link_libraries(ANA_SimpleAllocationOperatorsChecker PRIVATE
  clangAnalysis
  clangAST
  clangStaticAnalyzerCore
  clangStaticAnalyzerFrontend
  )

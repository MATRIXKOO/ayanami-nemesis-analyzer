set(LLVM_LINK_COMPONENTS
  Support
  )

set(LLVM_EXPORTED_SYMBOL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ANATestPlugin.exports)
add_llvm_library(ANATestPlugin MODULE BUILDTREE_ONLY MainCallChecker.cpp)

target_link_libraries(ANATestPlugin PRIVATE
  clangAnalysis
  clangAST
  clangStaticAnalyzerCore
  clangStaticAnalyzerFrontend
  )

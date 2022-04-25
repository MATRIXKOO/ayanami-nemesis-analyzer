add_library(function-printer STATIC
  PrintFunctionsAction.cpp
)

link_directories("${LLVM_LIBRARY_DIR}")
add_llvm_library(function-printer-plugin MODULE PrintFunctionsAction.cpp PLUGIN_TOOL clang)


install(TARGETS function-printer DESTINATION lib)


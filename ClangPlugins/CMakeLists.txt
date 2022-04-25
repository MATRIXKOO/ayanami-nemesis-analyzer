message("Found LLVM version: ${LLVM_DIR}")
message("Found Clang version: ${Clang_DIR}")

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
include(ChooseMSVCCRT)

include(AddLLVM)
include(HandleLLVMOptions)
find_package(Clang REQUIRED)
find_package(LLVM REQUIRED)

# Now set the LLVM header and library paths:
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})


include_directories(function-printer)

include_directories("${LLVM_INCLUDE_DIR}" "${CLANG_INCLUDE_DIRS}")
add_definitions("${LLVM_DEFINITIONS}")

link_directories("${LLVM_LIBRARY_DIR}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(
  "$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-fno-rtti;-Wall>"
  "$<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:DEBUG>>:-fno-omit-frame-pointer>"
)

# add subdirectory
add_subdirectory(function-printer)
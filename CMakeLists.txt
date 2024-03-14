cmake_minimum_required(VERSION 3.28)
project(nativity C CXX)

# set(CMAKE_C_COMPILER clang)
# set(CMAKE_CXX_COMPILER clang++)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#find_package(LLVM REQUIRED CONFIG)

#message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
#message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
#message(STATUS "Libraries located in: ${LLVM_LIBRARY_DIRS}")
#
#if(LLVM_ENABLE_RTTI)
#    message(STATUS "LLVM was built with RTTI")
#else()
#    message(STATUS "LLVM was not built with RTTI")
#endif()
#
#include_directories(${LLVM_INCLUDE_DIRS})
#link_directories(${LLVM_LIBRARY_DIRS})
#add_definitions(${LLVM_DEFINITIONS})

#
#find_library(LLVM NAMES libLLVM.so PATHS ${LLVM_LIBRARY_DIRS} NO_DEFAULT_PATH)
#
#message(STATUS "using find_library")
#find_library(LLD_COFF NAMES liblldCOFF.so PATHS ${LLVM_LIBRARY_DIRS} NO_DEFAULT_PATH)
#find_library(LLD_COMMON NAMES liblldCommon.so PATHS ${LLVM_LIBRARY_DIRS} NO_DEFAULT_PATH)
#find_library(LLD_ELF NAMES liblldELF.so PATHS ${LLVM_LIBRARY_DIRS} NO_DEFAULT_PATH)
#find_library(LLD_MACHO NAMES liblldMachO.so PATHS ${LLVM_LIBRARY_DIRS} NO_DEFAULT_PATH)
#`find_library(LLD_MINGW NAMES liblldMinGW.so PATHS ${LLVM_LIBRARY_DIRS} NO_DEFAULT_PATH)
#find_library(LLD_WASM NAMES liblldWasm.so PATHS ${LLVM_LIBRARY_DIRS} NO_DEFAULT_PATH)

add_compile_options(-fdiagnostics-color=always -funsigned-char -Werror -Wall -Wpedantic -Wextra)
set (NATIVITY_SOURCE_FILES
    bootstrap/nativity.c
)

add_executable(nativity ${NATIVITY_SOURCE_FILES})

# target_link_libraries(nativity ${LLVM})

#pragma once

#if defined(_MSC_VER)
#define COMPILER_MSVC 1
#elif defined(__clang__)

#define COMPILER_CLANG 1

#if defined(__APPLE__) && defined(__MACH__)
#define OS_MAC 1
#elif defined(__gnu_linux__)
#define OS_LINUX 1
#else
#error Clang used but OS is not supported
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#define ARCH_X86_64 1
#else 
#error Architecture not suported
#endif

#elif defined(__GNUC__) || defined(__GNUG__)

#define COMPILER_GCC 1

#if defined(__APPLE__) && defined(__MACH__)
#define OS_MAC 1
#elif defined(__gnu_linux__)
#define OS_LINUX 1
#else
#error GCC used but OS is not supported
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#define ARCH_X86_64 1
#else 
#error Architecture not suported
#endif

#else
#error Compiler is not supported
#endif

#if defined(__cplusplus)
#define LANGUAGE_CPP 1
#else
#define LANGUAGE_C 1
#endif

#if !defined(ARCH_X86_64)
#define ARCH_X86_64 0
#endif

#if !defined(ARCH_AARCH64)
#define ARCH_AARCH64 0
#endif

#if !defined(COMPILER_MSVC)
#define COMPILER_MSVC 0
#endif

#if !defined(COMPILER_CLANG)
#define COMPILER_CLANG 0
#endif

#if !defined(COMPILER_GCC)
#define COMPILER_GCC 0
#endif

#if !defined(OS_WINDOWS)
#define OS_WINDOWS 0
#endif

#if !defined(OS_LINUX)
#define OS_LINUX 0
#endif

#if !defined(OS_MAC)
#define OS_MAC 0
#endif

#if !defined(LANGUAGE_CPP)
#define LANGUAGE_CPP 0
#endif

#if !defined(LANGUAGE_C)
#define LANGUAGE_C 0
#endif

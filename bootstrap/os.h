#pragma once

#define arena_impl_reserve os_reserve
#define arena_impl_release os_release
#define arena_impl_commit os_commit
#define arena_impl_decomit os_decommit

#include "os/core.h"

#if OS_WINDOWS
#error todo
#elif OS_LINUX

#include "os/posix.h"

#elif OS_MACOS
#include "os/posix.h"
#else
#error todo
#endif


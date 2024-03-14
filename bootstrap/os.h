#pragma once

#define arena_impl_reserve os_reserve
#define arena_impl_release os_release
#define arena_impl_commit os_commit
#define arena_impl_decomit os_decommit

#include "os/core.h"

#if OS_WINDOWS
#include "os/windows.h"
#elif OS_LINUX
#include "os/linux.h"

#elif OS_MACOS
#error todo
#else
#error todo
#endif


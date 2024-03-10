#pragma once
#include "base.h"

#include "os/core.c"

#if OS_WINDOWS
#include "os/windows.c"
#elif OS_LINUX
#include "os/posix.c"
#elif OS_MAC
#include "os/posix.c"
#else
#error todo
#endif


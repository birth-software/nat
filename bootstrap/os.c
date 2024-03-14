#pragma once
#include "base.h"

#include "os/core.c"

#if OS_WINDOWS
#include "os/windows.c"
#elif OS_LINUX
#include "os/linux.c"
#elif OS_MAC
#error todo
#else
#error todo
#endif


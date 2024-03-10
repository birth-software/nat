#pragma once

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

void* os_reserve(u64 size)
{
    void* result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);
    return result;
}

void os_commit(void* pointer, u64 size)
{
    VirtualAlloc(pointer, size, MEM_COMMIT, PAGE_READWRITE);
}

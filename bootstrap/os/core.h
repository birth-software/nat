#pragma once

#include "../base.h"

typedef struct OS_Handle OS_Handle;
struct OS_Handle {
    u64 value;
};

typedef struct OS_AccessFlags OS_AccessFlags;
struct OS_AccessFlags {
    u32 read: 1;
    u32 write: 1;
    u32 execute: 1;
    u32 create_new : 1;
    u32 shared: 1;
};

// static OS_Handle os_file_open(String8 file_path, OS_AccessFlags access_flags);
// static String8 os_file_read(Arena* arena, OS_Handle file_handle, Range1u64 range);
void* os_reserve(u64 size);
void os_commit(void* pointer, u64 size);

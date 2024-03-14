#pragma once

#include "../base.h"

typedef struct OS_Handle OS_Handle;
struct OS_Handle {
#if OS_WINDOWS
    void* value;
#elif OS_LINUX
    int value;
#elif OS_MACOS
    int value;
#else
#error
#endif
};

typedef struct OS_AccessFlags OS_AccessFlags;
struct OS_AccessFlags {
    u32 read: 1;
    u32 write: 1;
    u32 execute: 1;
    u32 create_new : 1;
    u32 shared: 1;
};

typedef struct OS_FileAttributes OS_FileAttributes;
struct OS_FileAttributes
{
    u64 size;
};

static b32 os_init(void);

static String8 os_file_read_all(Arena* arena, String8 file_path);

static OS_Handle os_file_handle_acquire(String8 file_path, OS_AccessFlags access_flags);
static void os_file_handle_release(OS_Handle file_handle);
// static b32 os_file_handle_is_valid(OS_Handle file_handle);
static OS_FileAttributes os_file_handle_get_attributes(OS_Handle file_handle);
static String8 os_file_handle_read(Arena* arena, OS_Handle file_handle, Range1u64 range);
static void* os_reserve(u64 size);
static void os_commit(void* pointer, u64 size);

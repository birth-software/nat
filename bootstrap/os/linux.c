#pragma once

#include "core.h"

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>

int invalid_file_handle = -1;

typedef struct OS_LinuxState OS_LinuxState;
struct OS_LinuxState
{
    u64 page_size;
    struct timespec ts;
    Arena* arena;
};

OS_LinuxState* os_linux_state;

b32 os_init(void)
{
    Arena* arena = arena_allocate(gigabytes(1));
    u64 page_size = getpagesize();
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

    os_linux_state = push_array(arena, OS_LinuxState, 1);
    *os_linux_state = (OS_LinuxState)
    {
        .page_size = page_size,
        .ts = ts,
        .arena = arena,
    };

    return true;
}

// b32 os_file_handle_is_valid(OS_Handle file_handle)
// {
//     return file_handle.value != -1;
// }

OS_Handle os_file_handle_acquire(String8 file_path, OS_AccessFlags access_flags)
{
    int flags = 0;
    if (access_flags.read & !access_flags.write) {
        flags |= O_RDONLY;
    } else if (access_flags.write & !access_flags.read) {
        flags |= O_WRONLY;
    } else {
        flags |= O_RDWR;
    }

    int handle = open((char*)file_path.pointer, flags);

    return (OS_Handle) {
        .value = handle,
    };
}

void os_file_handle_release(OS_Handle file_handle)
{
    int fd = file_handle.value;
    close(fd);
}

OS_FileAttributes os_file_handle_get_attributes(OS_Handle file_handle)
{
    OS_FileAttributes file_attributes = {};

    int fd = file_handle.value;
    struct stat attributes;
    if (fstat(fd, &attributes) != -1)
    {
        file_attributes = (OS_FileAttributes) {
            .size = attributes.st_size,
        };
    }

    return file_attributes;
}

String8 os_file_handle_read(Arena* arena, OS_Handle file_handle, Range1u64 range)
{
    String8 result = {};
    int fd = file_handle.value;
    if (fd != invalid_file_handle)
    {
        u64 byte_to_read_count = Dim1u64(range);
        u64 offset = range.min;
        result.pointer = push_array_no_zero(arena, u8, byte_to_read_count);
        result.length = 0;
        u8* pointer = result.pointer;
        u8* end = result.pointer + byte_to_read_count;

        while (true)
        {
            u64 unread = (u64)(end - pointer);
            u64 bytes_to_read = max(unread, 0x7ffff000);
            ssize_t syscall_result = pread(fd, pointer, bytes_to_read, offset);
            if (syscall_result == -1)
            {
                // TODO: set error
                break;
            }

            if (syscall_result == 0)
            {
                break;
            }

            u64 iteration_read_byte_count = (u64)syscall_result;
            pointer += iteration_read_byte_count;
            result.length += iteration_read_byte_count;

            if (pointer >= end)
            {
                break;
            }
        }
    }
    else
    {
        // TODO: error
    }

    return result;
}

void* os_reserve(u64 size)
{
    void* result = mmap(0, size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1 , 0);
    return result;
}

void os_commit(void* pointer, u64 size)
{
    mprotect(pointer, size, PROT_READ|PROT_WRITE);
}

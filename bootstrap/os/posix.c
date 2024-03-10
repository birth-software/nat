#pragma once

#include "core.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int invalid_file_handle = -1;

// OS_Handle os_file_open(String8 file_path, OS_AccessFlags access_flags)
// {
//     int flags = 0;
//     if (access_flags.read & !access_flags.write) {
//         flags |= O_RDONLY;
//     } else if (access_flags.write & !access_flags.read) {
//         flags |= O_WRONLY;
//     } else {
//         flags |= O_RDWR;
//     }
//
//     int handle = open((char*)file_path.pointer, flags);
//
//     return (OS_Handle) {
//         .value = handle,
//     };
// }
//
// String8 os_file_read(Arena* arena, OS_Handle file_handle, Range1u64 range)
// {
//     String8 result = {};
//     int fd = file_handle.value;
//     if (fd != invalid_file_handle) {
//         u64 byte_to_read_count = Dim1u64(range);
//         u64 read_byte_count = 0;
//         unused(read_byte_count);
//         unused(byte_to_read_count);
//         // push_array_no_zero();
//         //pread(fd, byte_to_read_count);
// // extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
// // 		      __off_t __offset) __wur
//     } else {
//         // TODO: error
//     }
//     unused(arena);
//     unused(file_handle);
//     unused(range);
//     return result;
// }

void* os_reserve(u64 size)
{
    void* result = mmap(0, size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1 , 0);
    return result;
}

void os_commit(void* pointer, u64 size)
{
  mprotect(pointer, size, PROT_READ|PROT_WRITE);
}

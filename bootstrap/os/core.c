#pragma once
#include "../base.h"
#include "../os.h"

String8 os_file_read_all(Arena* arena, String8 file_path)
{
    OS_Handle file_handle = os_file_handle_acquire(file_path, (OS_AccessFlags) {
        .read = true,
    });
    OS_FileAttributes file_attributes = os_file_handle_get_attributes(file_handle);

    String8 file_slice = os_file_handle_read(arena, file_handle, (Range1u64) { .min = 0, .max = file_attributes.size });

    os_file_handle_release(file_handle);

    return file_slice;
}


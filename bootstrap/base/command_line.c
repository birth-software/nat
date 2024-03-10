#pragma once

#include "../base.h"

CommandLine command_line_from_string_list(Arena* arena, String8List strings)
{
    unused(arena);
    // TODO:
    return (CommandLine) {
        .strings = strings,
    };
}

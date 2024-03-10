#pragma once

#include "../base.h"

typedef struct CommandLine CommandLine;
struct CommandLine
{
    // TODO:
    String8List strings;
};
static CommandLine command_line_from_string_list(Arena* arena, String8List strings);

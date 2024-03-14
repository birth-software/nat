#pragma once

#include "../base.h"
#include "../os.h"

static void base_main_thread_entry(void (*entry)(CommandLine* command_line), u64 argument_count, const char** argument_pointer, const char** environment_pointer)
{
    unused(environment_pointer);
    ThreadContext context = thread_context_allocate();
    context.is_main_thread = true;
    thread_context_set(&context);

    String8List argument_list = {};
    for (u64 argument_index = 0; argument_index < argument_count; argument_index += 1)
    {
        str8list_push(context.scratch_arenas[0], &argument_list, str8_from_c(argument_pointer[argument_index]));
    }

    CommandLine command_line = command_line_from_string_list(context.scratch_arenas[0], argument_list);

    b32 os_init_result = os_init();
    check(os_init_result);
    entry(&command_line);
}

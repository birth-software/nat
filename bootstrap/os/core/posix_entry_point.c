#pragma once

#include "../../base.h"

static void entry_point(CommandLine* command_line);

int main(int argument_count, const char* argument_pointer[], const char** enviroment_pointer)
{
    base_main_thread_entry(&entry_point, (u64)argument_count, argument_pointer, enviroment_pointer);
}


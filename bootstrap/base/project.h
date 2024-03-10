#pragma once
#include "../base.h"
static void base_main_thread_entry(void (*entry)(CommandLine* command_line), u64 argument_count, const char** argument_pointer, const char** environment_pointer);

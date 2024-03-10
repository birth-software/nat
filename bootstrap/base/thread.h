#pragma once

#include "../base.h"

#define thread_scratch_arena_count (2)
typedef struct ThreadContext ThreadContext;
struct ThreadContext
{
    Arena* scratch_arenas[thread_scratch_arena_count];
    u32 thread_name_len;
    b32 is_main_thread;
    u8 thread_name[64];
};

static ThreadContext thread_context_allocate(void);
static void thread_context_set(ThreadContext* context);
static ArenaTemporary thread_begin_scratch_arena(Arena** conflicts, u64 conflict_count);

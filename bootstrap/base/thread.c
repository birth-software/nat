#pragma once
#include "../base.h"

threadlocal ThreadContext* thread_context;

ThreadContext thread_context_allocate(void)
{
    ThreadContext context = {};

    for (u32 arena_index = 0; arena_index < array_count(context.scratch_arenas); arena_index += 1)
    {
        context.scratch_arenas[arena_index] = arena_allocate(gigabytes(8));
    }

    return context;
}

ArenaTemporary thread_begin_scratch_arena(Arena** conflicts, u64 conflict_count)
{
    ArenaTemporary scratch = {};
    for (u32 scratch_arena_index = 0; scratch_arena_index < array_count(thread_context->scratch_arenas); scratch_arena_index += 1)
    {
        b32 is_conflicting = false;
        for (Arena** conflict = conflicts; conflict < conflicts + conflict_count; conflict += 1)
        {
            if (*conflict == thread_context->scratch_arenas[scratch_arena_index])
            {
                is_conflicting = true;
                break;
            }
        }

        if (!is_conflicting)
        {
            scratch.arena = thread_context->scratch_arenas[scratch_arena_index];
            scratch.position = scratch.arena->position;
            break;
        }
    }

    return scratch;
}

void thread_context_set(ThreadContext* context)
{
    thread_context = context;
}

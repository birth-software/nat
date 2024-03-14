#pragma once
#include "../base.h"
#include "../os.h"

Arena* arena_allocate(u64 requested_size)
{
    u64 size_roundup_granularity = megabytes(64);
    u64 size = requested_size;
    size += size_roundup_granularity;
    size -= size % size_roundup_granularity;
    void* block = arena_impl_reserve(size);
    u64 initial_commit_size = arena_commit_granularity;
    check(initial_commit_size >= sizeof(Arena));
    arena_impl_commit(block, initial_commit_size);
    Arena* arena = (Arena*) block;
    *arena = (Arena){
        .position = sizeof(Arena),
        .commit_position = initial_commit_size,
        .alignment = 8,
        .size = size,
    };

    return arena;
}

void* arena_push(Arena* arena, u64 size)
{
    void* result = arena_push_no_zero(arena, size);
    memory_zero(result, size);
    return result;
}

u64 arena_get_position_without_self(Arena* arena)
{
    return arena->position - sizeof(Arena);
}

void* arena_push_no_zero(Arena* arena, u64 size)
{
    void* result = 0;
    if (arena->position + size <= arena->size)
    {
        u8* base = (u8*)arena;
        u64 post_alignment_position = (arena->position + (arena->alignment - 1));
        post_alignment_position -= post_alignment_position % arena->alignment;
        u64 alignment = post_alignment_position - arena->position;
        result = base + arena->position + alignment;
        arena->position += size + alignment;

        if (arena->commit_position < arena->position)
        {
            u64 size_to_commit = arena->position - arena->commit_position;
            size_to_commit += arena_commit_granularity - 1;
            size_to_commit -= size_to_commit % arena_commit_granularity;
            arena_impl_commit(base + arena->commit_position, size_to_commit);
            arena->commit_position += size_to_commit;
        }
    }
    else
    {
        // fail
    }

    return result;
}

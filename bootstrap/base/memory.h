#pragma once
#include "core.h"

const u64 arena_commit_granularity = kilobytes(4);
typedef struct Arena Arena;
struct Arena{
    u64 position;
    u64 commit_position;
    u64 alignment;
    u64 size;
    Arena* ptr;
    u64 unused[3];
};

typedef struct ArenaTemporary ArenaTemporary;
struct ArenaTemporary{
    Arena* arena;
    u64 position;
};

static Arena* arena_allocate(u64 size);
static void* arena_push(Arena* arena, u64 size);
static void* arena_push_no_zero(Arena* arena, u64 size);
static u64 arena_get_position_without_self(Arena* arena);

#define push_array_no_zero(arena, type, count) (type*)arena_push_no_zero((arena), sizeof(type) * (count))
#define push_array(arena, type, count) (type*)arena_push((arena), sizeof(type) * (count))

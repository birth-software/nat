#pragma once

#include "../base.h"

typedef struct String8 String8;
struct String8
{
    u8* pointer;
    u64 length;
};

typedef struct String8Node String8Node;
struct String8Node
{
    String8 string;
    String8Node* next;
};

typedef struct String8List String8List;
struct String8List
{
    String8Node* first;
    String8Node* last;
    u64 node_count;
    u64 total_size;
};

#define str8_from_c(cstring) (String8) { .pointer = (u8*)(cstring), .length = c_string_length(cstring), }
#define str8_literal(literal) (String8) { .pointer = (u8*)(literal), .length = sizeof(literal) - 1, }

static u64 c_string_length(const char* cstring);

static void str8list_push_node(String8List* list, String8Node* node);
static void str8list_push(Arena* arena, String8List* list, String8 string);

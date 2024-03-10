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

#define str8(ptr, len) (String8){ .pointer = (ptr), .length = (len) }
#define str8_from_c(cstring) str8((u8*)(cstring), c_string_length(cstring))

static u64 c_string_length(const char* cstring);

static void str8list_push_node(String8List* list, String8Node* node);
static void str8list_push(Arena* arena, String8List* list, String8 string);

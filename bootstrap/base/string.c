#pragma once

#include "../base.h"

void str8list_push_node(String8List* list, String8Node* node)
{
    queue_push(list->first, list->last, node);
    list->node_count += 1;
    list->total_size += node->string.length;
}

void str8list_push(Arena* arena, String8List* list, String8 string)
{
    String8Node* node = push_array(arena, String8Node, 1);
    node->string = string;
    str8list_push_node(list, node);
}

u64 c_string_length(const char* cstring)
{
    u64 len = 0;
    while (cstring[len])
    {
        len += 1;
    }

    return len;
}

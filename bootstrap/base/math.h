#pragma once

#include "core.h"

typedef union Range1u64 Range1u64;
union Range1u64
{
    struct
    {
        u64 min;
        u64 max;
    };
    u64 v[2];
};

u64 Dim1u64(Range1u64 range);

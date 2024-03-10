#pragma once

#include "../base.h"

u64 Dim1u64(Range1u64 range)
{
    return range.max - range.min;
}

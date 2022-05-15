#pragma once
#include "float.h"

class Range
{
    public:
        Range() = default;
        Range(float _min, float _max) { min = _min; max = _max; }
        Range(float minMax) { min = minMax; max = minMax; }
        ~Range() {}

        bool intersectRange(Range) const;
        Range valueInRange(float) const;

        float min;
        float max;
};
#pragma once
#include <stdlib.h>

#include "../toolbox/range.h"

namespace maths
{
    const float TAU = 6.283185307179586476925286f;
    const float mathPI = 3.141592653589793238462643f;

    float clamp2f(float x, float min, float max);
    float sign(float value);

    template <typename T>
    T     lerp(T x, T y, float a);

    float min(float x, float y);
    float max(float x, float y);
    float saturate(float v);
    float randRange(Range r);
    float toRadians(float angle);
}
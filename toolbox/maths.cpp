#include "maths.h"

float maths::clamp2f(float x, float min, float max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    else
        return x;
}

float maths::sign(float value)
{
    return (value >= 0 ? 1.f : -1.f);
}

template <typename T>
T maths::lerp(T x, T y, float a)
{
    return x * (1 - a) + y * a;
}
float maths::min(float x, float y)
{
    return (x < y) ? x : y;
}
float maths::max(float x, float y)
{
    return (x > y) ? x : y;
}
float maths::saturate(float v)
{
    return max(0.f, min(1.f, v));
}
float maths::randRange(Range r)
{
    float rnd = (rand() % RAND_MAX) / (float)RAND_MAX;
    return maths::lerp(r.min, r.max, rnd);
}

float maths::toRadians(float angle)
{
    return angle * maths::TAU / 360.f;
}
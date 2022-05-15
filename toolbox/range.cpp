#include "range.h"

bool Range::intersectRange(Range r) const
{
    return !(this->min > r.max || r.min > this->max);
}

Range Range::valueInRange(float value) const
{
    Range r;
    r.min = this->min > value ? value : min;
    r.max = this->max < value ? value : max;
    return r;
}
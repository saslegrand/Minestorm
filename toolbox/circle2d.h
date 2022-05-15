#pragma once

#include "vector2d.h"

class Circle2D
{
public:
	Circle2D() { radius = 0.f; }
	~Circle2D() {}

	Vector2D center;
	float    radius;
};
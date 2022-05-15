#pragma once
#include <raylib.h>

#include "../toolbox/referantial2d.h"

class Movement
{
public:
	Movement() {}
	~Movement(){}

	Vector2D velocity;
	float    speed      = 0.f;
	float    maxSpeed   = 0.f;
	float    drag       = 0.f;
	bool     isMaxSpeed = false;
};
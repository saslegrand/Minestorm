#pragma once
#include <raylib.h>

#include "../toolbox/vector2d.h"

class AABB
{
public:
	AABB();
	~AABB(){}

	void resetMinMax();

	void update(float valueX, float valueY);
	void updateMinMax(float valueX, float valueY);
	void updateColor(Color c);
	void draw() const;

	Vector2D pos;
	Vector2D center;
	Vector2D minPos;
	Vector2D maxPos;

	float	 width;
	float	 height;

	Color    color;
};
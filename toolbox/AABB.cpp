#include "AABB.h"
#include <float.h>

AABB::AABB()
{
	minPos = { FLT_MAX, FLT_MAX };
	maxPos = { -FLT_MAX, -FLT_MAX };
	width  = 0.f;
	height = 0.f;
	color  = WHITE;
}

void AABB::resetMinMax()
{
	minPos = { FLT_MAX, FLT_MAX };
	maxPos = { -FLT_MAX, -FLT_MAX };
}

void AABB::update(float valueX, float valueY)
{
	updateMinMax(valueX, valueY);

	pos = { minPos.x, minPos.y };
	width = maxPos.x - minPos.x;
	height = maxPos.y - minPos.y;

	center = { pos.x + width / 2.f, pos.y + height / 2.f };
}

void AABB::updateMinMax(float valueX, float valueY)
{
	minPos.x = minPos.x < valueX ? minPos.x : valueX;
	minPos.y = minPos.y < valueY ? minPos.y : valueY;
	maxPos.x = maxPos.x > valueX ? maxPos.x : valueX;
	maxPos.y = maxPos.y > valueY ? maxPos.y : valueY;
}

void AABB::updateColor(Color c)
{
	color = c;
}

void AABB::draw() const
{
	DrawRectangleLines((int)pos.x, (int)pos.y, (int)width, (int)height, color);
}
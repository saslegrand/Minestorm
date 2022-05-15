#pragma once

#include "animation.h"

class BulletExplosion : public Animation
{
public:
	BulletExplosion(Vector2D origin, Color color);
	~BulletExplosion() {}
};
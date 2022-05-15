#pragma once

#include "animation.h"

class PlayerExplosion : public Animation
{
public:
	PlayerExplosion(Vector2D origin, Color color);
	~PlayerExplosion() {}
};
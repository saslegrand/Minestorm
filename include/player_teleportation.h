#pragma once

#include "animation.h"

class PlayerTeleportation : public Animation
{
public:
	PlayerTeleportation(Vector2D origin, Color color);
	~PlayerTeleportation() {}
};
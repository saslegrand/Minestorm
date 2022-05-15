#pragma once
#include <raylib.h>

#include "entity.h"

enum class MineType
{
	FLOATING,
	MAGNETIC,
	FIREBALL,
	MAGNETIC_FIREBALL
};

enum class MineSize
{
	BIG,
	MEDIUM,
	SMALL
};

class Mine : public Entity
{
public:
	Mine() = default;
	~Mine() {}

	void draw()		 const override = 0;
	void drawDebug() const override = 0;
	void update()		   override = 0;
	void updateMovement()  override = 0;

	MineSize m_size;
	MineType m_type;

	int		 deathScore = 0;
	float    scale;
	Vector2D dir;
};
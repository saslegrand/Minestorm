#pragma once

#include "mines.h"
#include "static_mine_movement.h"

class FloatingMine : public Mine
{
public:
	FloatingMine(float scale, MineSize _size, int score, Vector2D origin);
	~FloatingMine();

	void draw() const override;
	void drawDebug() const override;
	void update() override;
	void updateMovement() override;

private:
	StaticMineMovement m_movement;
};
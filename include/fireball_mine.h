#pragma once

#include "mines.h"
#include "static_mine_movement.h"

class FireballMine : public Mine
{
public:
	FireballMine(float scale, MineSize _size, int score, Vector2D origin);
	~FireballMine();

	void draw() const override;
	void drawDebug() const override;
	void update() override;
	void updateMovement() override;

private:
	StaticMineMovement m_movement;
};
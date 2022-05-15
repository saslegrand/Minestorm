#pragma once
#include "mines.h"
#include "static_mine_movement.h"

class MagneticMine : public Mine
{
public:
	MagneticMine(float scale, MineSize _size, int score, Vector2D origin);
	~MagneticMine();

	inline void setTarget(Vector2D target) { m_target = target; }
	void draw() const override;
	void drawDebug() const override;
	void update() override;
	void updateMovement() override;

private:
	StaticMineMovement m_movement;
	Vector2D           m_target;
};
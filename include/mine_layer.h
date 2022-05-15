#pragma once

#include "entity.h"
#include "static_mine_movement.h"
#include "mines.h"

class MineLayer : public Entity
{
public:
	MineLayer();
	~MineLayer() {}

	inline void setMaxSpeed(float maxSpeed) { m_movement.maxSpeed = maxSpeed; }
	void		update() override;
	void	    updateMovement()  override;
	void		updateTarget();

	void		initShapes();

	bool isAlive = false;

	Vector2D target;
	Vector2D m_dir;
	int      deathScore;

private:
	StaticMineMovement m_movement;
};
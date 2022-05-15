#pragma once

#include "entity.h"
#include "static_mine_movement.h"
#include "mines.h"

class SpawnMotherShip : public Entity
{
public:
	SpawnMotherShip();
	~SpawnMotherShip() {}

	void update()		   override;
	void updateMovement()  override;
	void reset();

	std::vector<Vector2D> spawns;
	std::vector<bool>     isSpawn;

private:
	StaticMineMovement    m_movement;
};
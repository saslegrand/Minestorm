#pragma once
#include <raylib.h>

#include "entity.h"
#include "player_movement.h"

const float MAX_SPEED = 700.f;
const float SPEED	  = 50.f;
const float DRAG	  = 0.08f;

struct PlayerInputs
{
	int m_keyShoot;
	int m_keyRot[2];
	int m_keyMove;
	int m_keyTeleport[2];
};

class Player : public Entity
{
public:
	Player() = default;
	Player(int index, const Texture2D& texture, Sounds* sounds);
	~Player() {}

	Color getColor() { return m_statTexture.color; }
	void resetPlayer();
	void update()		  override;
	void updateMovement() override;
	void updateShoot();
	void checkEventTeleportation();

	bool	 isShooting = false;
	Vector2D initialOrigin;
	int      life = 3;
	bool     isAlive = true;
	bool     isTeleport = false;

private:
	PlayerInputs   m_inputs;
	Timer		   m_timerShoot;
	Timer		   m_timerTeleport;
	PlayerMovement m_movement;
};
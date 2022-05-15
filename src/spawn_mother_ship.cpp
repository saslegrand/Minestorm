#include "../include/spawn_mother_ship.h"
#include "../include/game.h"
#include "../include/utils.h"
#include "../toolbox/maths.h"

SpawnMotherShip::SpawnMotherShip()
{
	m_localRef.origin    = { (float)SCREEN_WIDTH / 2.f, 0.f };
	m_statTexture.color  = RED;
	m_statTexture.width  = 512.f;
	m_statTexture.height = 256.f;
	m_statTexture.src    = { 512.f, 0.f, 256.f, 256.f };
	m_movement           = { 250.f, 250.f, 0.f };

	m_localRef.rotateRef(maths::toRadians(180.f));
}

void SpawnMotherShip::reset()
{
	spawns.clear();
	isSpawn.clear();
	m_localRef = {};
	m_localRef.origin = { (float)SCREEN_WIDTH / 2.f, 0.f };
	m_statTexture.color = RED;
	m_statTexture.width = 512.f;
	m_statTexture.height = 256.f;
	m_statTexture.src = { 512.f, 0.f, 256.f, 256.f };
	m_movement = { 200.f, 200.f, 0.f };

	m_localRef.rotateRef(maths::toRadians(180.f));
}

void SpawnMotherShip::updateMovement()
{
	m_movement.updateAcceleration(m_localRef.unitJ);
	m_movement.updatePosition(m_localRef, m_deltaTime);
}

void SpawnMotherShip::update()
{
	m_deltaTime = GetFrameTime();
	updateMovement();
}
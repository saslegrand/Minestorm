#include <iostream>
#include <string>

#include "../include/player.h"
#include "../include/game.h"
#include "../toolbox/range.h"
#include "../include/utils.h"

const float ROT_ANGLE = 4.F * maths::mathPI / 180.f;

void checkBorderBullets(std::vector<Bullet>& bullets, float offsetX, float offsetY, float dir)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (offsetX != 0.f)
			bullets[i].circle.center.x += offsetX * dir;
		if (offsetY != 0.f)
			bullets[i].circle.center.y += offsetY * dir;
	}
}

void initShapes(Collider& collider, Vector2D origin)
{
	collider.shapes.clear();
	std::vector<Vector2D> shape;

	shape.push_back({ origin.x, origin.y });
	shape.push_back({ origin.x - 4.f, origin.y - 6.f });
	shape.push_back({ origin.x, origin.y - 18 });
	shape.push_back({ origin.x + 4.f, origin.y - 6.f });

	collider.addShape(shape, 4);
	shape.clear();

	shape.push_back({ origin.x, origin.y });
	shape.push_back({ origin.x + 6.f, origin.y - 2.f });
	shape.push_back({ origin.x + 7.f, origin.y + 12.f });

	collider.addShape(shape, 3);
	shape.clear(); 
	
	shape.push_back({ origin.x, origin.y });
	shape.push_back({ origin.x - 6.f, origin.y - 2.f });
	shape.push_back({ origin.x - 7.f, origin.y + 12.f });

	collider.addShape(shape, 3);
	shape.clear();
}

void setInputsColor(TextureStat& stat, PlayerInputs& inputs, int index)
{
	if (index == -1)
	{
		stat.color = DARKGREEN;
		inputs.m_keyShoot = KEY_K;
		inputs.m_keyRot[0] = KEY_L;
		inputs.m_keyRot[1] = KEY_J;
		inputs.m_keyMove = KEY_I;
		inputs.m_keyTeleport[0] = KEY_U;
		inputs.m_keyTeleport[1] = KEY_O;
		stat.src = { 0.f, 512.f, 256.f, 256.f };
	}
	else
	{
		stat.color = SKYBLUE;
		inputs.m_keyShoot = KEY_F;
		inputs.m_keyRot[0] = KEY_G;
		inputs.m_keyRot[1] = KEY_D;
		inputs.m_keyMove = KEY_R;
		inputs.m_keyTeleport[0] = KEY_E;
		inputs.m_keyTeleport[1] = KEY_T;
		stat.src = { 0.f, 0.f, 256.f, 256.f };
	}
}

Player::Player(int index, const Texture2D& texture, Sounds* sounds)
{
	float offsetX	  = 139.f;
	m_localRef.origin = { (float)SCREEN_WIDTH / 2 - (offsetX * index), (float)SCREEN_HEIGHT / 2 };
	initialOrigin     = m_localRef.origin;

	setInputsColor(m_statTexture, m_inputs, index);

	initShapes(m_collider, m_localRef.origin);
	m_collider.updateAABB();
	m_movement = PlayerMovement(MAX_SPEED, SPEED, DRAG);

	m_timerShoot.setDelay(0.11f);
	m_statTexture.width = (float)PLAYER_WIDTH;
	m_statTexture.height = (float)PLAYER_HEIGHT;

	m_texture = texture;
	m_sounds = sounds;
}

void Player::updateShoot()
{
	if (IsKeyDown(m_inputs.m_keyShoot))
	{
		m_timerShoot.update();

		if (m_timerShoot.isDelayPassed)
		{
			m_timerShoot.isDelayPassed = false;
			isShooting = true;
			PlaySoundMulti(m_sounds->playerShoot);
		}
	}
	else
	{
		m_timerShoot.setTime();
	}
}

void Player::resetPlayer()
{
	m_localRef.reset();
	m_localRef.origin = initialOrigin;
	initShapes(m_collider, m_localRef.origin);
	m_collider.updateAABB();
	m_movement.velocity = { 0.f, 0.f };

	if (life != 0)
		isAlive = true;
}

void Player::checkEventTeleportation()
{
	if ((IsKeyPressed(m_inputs.m_keyTeleport[0]) || IsKeyPressed(m_inputs.m_keyTeleport[1])) && !isTeleport)
	{
		m_timerTeleport.reset();
		m_timerTeleport.setDelay(0.3f);
		isTeleport = true;
		PlaySound(m_sounds->playerTeleport);
		m_collider = { };
	}

	if (isTeleport)
	{
		m_timerTeleport.update();

		if (m_timerTeleport.isDelayPassed)
		{
			Range X = { (float)SCREEN_PADDING, (float)SCREEN_WIDTH - (float)SCREEN_PADDING };
			Range Y = { (float)SCREEN_PADDING, (float)SCREEN_HEIGHT - (float)SCREEN_PADDING };

			m_localRef.origin.x = maths::randRange(X);
			m_localRef.origin.y = maths::randRange(Y);

			initShapes(m_collider, m_localRef.origin);
			m_collider.updateShapesRotation(m_localRef.origin, m_localRef.angle);

			isTeleport = false;
		}
	}
}

void Player::updateMovement()
{
	static bool isDown = false;

	if (IsKeyDown(m_inputs.m_keyMove))
	{
		m_movement.updateAcceleration(m_localRef);

		if (!isDown)
			PlaySound(m_sounds->playerShip);

		isDown = true;
	}
	else
		isDown = false;

	m_movement.updateDeceleration(m_localRef);

	if (IsKeyDown(m_inputs.m_keyRot[0]))
	{
		m_movement.updateRotation(m_localRef, ROT_ANGLE);
		m_collider.updateShapesRotation(m_localRef.origin, ROT_ANGLE);
	}

	if (IsKeyDown(m_inputs.m_keyRot[1]))
	{
		m_movement.updateRotation(m_localRef, -ROT_ANGLE);
		m_collider.updateShapesRotation(m_localRef.origin, -ROT_ANGLE);
	}

	m_movement.updatePosition(m_localRef, m_deltaTime);
	m_collider.updateShapesPosition(m_movement.velocity, m_deltaTime);

	checkEventTeleportation();
}

void Player::update()
{
	m_deltaTime = GetFrameTime();

	updateMovement();
	updateShoot();

	Entity::update();
}
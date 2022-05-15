#include "../include/bullet.h"

Bullet::Bullet(Vector2D pos, Vector2D dir, BulletType t, Color color)
{
	circle.center = pos;
	circle.radius = RADIUS;
	m_dir	   = dir;
	m_timer.setDelay(m_lifeTime);
	m_color = color;
	type = t;
}

void Bullet::update()
{
	m_deltaTime = GetFrameTime();

	if (type == BulletType::PLAYER_1 || type == BulletType::PLAYER_2)
	{
		m_timer.update();

		if (m_timer.isDelayPassed)
			isAlive = false;
	}

	circle.center += m_dir * m_speed * m_deltaTime;
}

void Bullet::drawBullet() const
{
	DrawCircle((int)circle.center.x, (int)circle.center.y, RADIUS, m_color);
}

void Bullet::drawFireball(const Texture2D& texture) const
{
	Rectangle src    = { 768.f, 0.f, 256.f, 256.f };
	Rectangle dest   = { circle.center.x, circle.center.y, 96.f, 96.f };
	Vector2   origin = { 48.f, 48.f };
	DrawTexturePro(texture, src, dest, origin, 0, WHITE);
}

Bullet& Bullet::operator=(const Bullet& bullet)
{
	circle = bullet.circle;
	m_dir = bullet.m_dir;
	m_timer = bullet.m_timer;
	isAlive = bullet.isAlive;
	m_color = bullet.m_color;

	return *this;
}
#pragma once

#include <raylib.h>

#include "../toolbox/circle2d.h"
#include "../include/timer.h"

const float RADIUS = 3.f;

enum class BulletType
{
	PLAYER_1 = 0,
	PLAYER_2 = 1,
	FIREBALL = 2
};

class Bullet
{
public:
	Bullet(Vector2D pos, Vector2D dir, BulletType t, Color color);
	~Bullet(){}

	inline Vector2D getPos() { return circle.center; }
	inline Color    getColor() { return m_color; }
	inline void	    setSpeed(float speed) { m_speed = speed; }
	inline void		setRadius(float radius) { circle.radius = radius; }

	void drawBullet() const;
	void drawFireball(const Texture2D& texture) const;
	void update();

	Bullet& operator=(const Bullet& bullet);

	Circle2D	circle;
	bool		isAlive = true;
	BulletType  type;

private:
	Vector2D	m_dir;
	float		m_speed    = 700.f;
	const float m_lifeTime = 1.03f;
	Timer		m_timer;
	Color		m_color;
	float		m_deltaTime;
};

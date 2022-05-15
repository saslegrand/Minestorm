#include "../include/bullet_explosion.h"
#include "../toolbox/maths.h"

BulletExplosion::BulletExplosion(Vector2D origin, Color color)
{
	for (int i = 0; i < 50; i++)
	{
		float lifeTime = maths::randRange({ 0.2f, 0.4f });
		float radius = maths::randRange({ 1.f, 1.5f });
		float speed = maths::randRange({ 50.f, 70.f });
		m_particles.push_back(Particles(origin, radius, speed, lifeTime, color));
		m_particles.back().getRef().rotateRef((float)GetRandomValue(0, 360) * maths::TAU / 360.f);
	}
}
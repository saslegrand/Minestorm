#include "../include/player_explosion.h"
#include "../toolbox/maths.h"

PlayerExplosion::PlayerExplosion(Vector2D origin, Color color)
{
	for (int i = 0; i < 100; i++)
	{
		float lifeTime = maths::randRange({ 0.5, 0.7f });
		float radius = maths::randRange({ 2.f, 2.5f });
		float speed = maths::randRange({ 50.f, 400.f });
		m_particles.push_back(Particles(origin, radius, speed, lifeTime, color));
		m_particles.back().getRef().rotateRef((float)GetRandomValue(0, 360) * maths::TAU / 360.f);
	}
}
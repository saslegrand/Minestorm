#include "../include/mine_explosion.h"
#include "../toolbox/maths.h"

MineExplosion::MineExplosion(Vector2D origin)
{
	for (int i = 0; i < 50; i++)
	{
		float lifeTime = maths::randRange({ 0.2f, 0.5f });
		float radius = maths::randRange({ 1.f, 2.f });
		float speed = maths::randRange({ 100.f, 300.f });
		m_particles.push_back(Particles(origin, radius, speed, lifeTime, RED));
		m_particles.back().getRef().rotateRef((float)GetRandomValue(0, 360) * maths::TAU / 360.f);
	}
}
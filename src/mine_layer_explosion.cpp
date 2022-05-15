#include "../include/mine_layer_explosion.h"
#include "../toolbox/maths.h"

MineLayerExplosion::MineLayerExplosion(Vector2D origin)
{
	for (int i = 0; i < 50; i++)
	{
		float lifeTime = maths::randRange({ 0.5f, 0.7f });
		float radius = maths::randRange({ 1.5f, 2.f });
		float speed = maths::randRange({ 50.f, 200.f });
		m_particles.push_back(Particles(origin, radius, speed, lifeTime, RED));
		m_particles.back().getRef().rotateRef((float)GetRandomValue(0, 360) * maths::TAU / 360.f);
	}
}
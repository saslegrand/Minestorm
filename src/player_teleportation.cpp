#include "../include/player_teleportation.h"
#include "../toolbox/maths.h"

PlayerTeleportation::PlayerTeleportation(Vector2D origin, Color color)
{
	for (int i = 0; i < 5; i++)
	{
		float lifeTime = maths::randRange({ 0.3f, 0.5f });
		float radius = maths::randRange({ 1.f, 1.5f });
		float speed = maths::randRange({ 20.f, 50.f });
		m_particles.push_back(Particles(origin, radius, speed, lifeTime, color));
		m_particles.back().getRef().rotateRef((float)GetRandomValue(0, 360) * maths::TAU / 360.f);
	}
}
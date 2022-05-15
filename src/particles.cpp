#include "../include/particles.h"

Particles::Particles(Vector2D origin, float radius, float speed, float lifeTime, Color color)
{
	m_localRef.origin = origin;
	m_radius		  = radius;
	m_speed			  = speed;
	m_color			  = color;

	m_timer.setDelay(lifeTime);
}

void Particles::draw() const
{
	DrawCircle((int)m_localRef.origin.x, (int)m_localRef.origin.y, m_radius, m_color);
}

void Particles::update()
{
	float deltaTime = GetFrameTime();

	m_timer.update();

	if (m_timer.isDelayPassed)
	{
		isAlive               = false;
		m_timer.isDelayPassed = false;
	}

	m_color.a		   = (int)((1.f - (m_timer.getTime() / m_timer.getDelay())) * 255.f);
	m_localRef.origin += m_localRef.unitJ * m_speed * deltaTime;
}
#include "../include/animation.h"

void Animation::draw() const
{
	for (unsigned int i = 0; i < m_particles.size(); i++)
	{
		if (m_particles[i].isAlive)
			m_particles[i].draw();
	}
}

void Animation::update()
{
	unsigned int i = 0;

	while (i < m_particles.size())
	{
		if (!m_particles[i].isAlive)
		{
			m_particles[i] = m_particles.back();
			m_particles.pop_back();
			i--;
			continue;
		}

		m_particles[i].update();

		i++;
	}
}
#pragma once
#include "timer.h"
#include "../toolbox/referantial2D.h"

class Particles
{
public:
	Particles() = default;
	Particles(Vector2D origin, float radius, float speed, float lifeTime, Color color);
	~Particles() {}

	inline Referantial2D& getRef() { return m_localRef; }

	void draw() const;
	void update();

	bool		  isAlive = true;

private:
	Timer	      m_timer;
	float         m_speed;
	float		  m_radius;
	Referantial2D m_localRef;
	Color		  m_color;
};
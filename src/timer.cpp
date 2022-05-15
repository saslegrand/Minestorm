#include "../include/timer.h"

#include <iostream>
#include <string>

Timer::Timer()
{
	m_delay = 0.f;
	m_prevTime = 0.f;
	m_time = 0.f;
}

void Timer::setTime()
{
	m_time = m_delay;
}

void Timer::reset()
{
	m_delay = 0.f;
	m_prevTime = 0.f;
	m_time = 0.f;
	isDelayPassed = false;
}

void Timer::update()
{
	m_time += GetFrameTime();

	if (m_time > m_delay)
	{
		isDelayPassed = true;
		m_time = 0.f;
	}
}
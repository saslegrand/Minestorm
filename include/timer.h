#pragma once

#include <raylib.h>

class Timer
{
public:
	Timer();
	~Timer(){}

	inline void    setDelay(float delay) { m_delay = delay; }
	inline double  getTime() { return m_time; }
	inline float   getDelay() { return m_delay; }
	void  setTime();
	void  update();
	void  reset();

	bool isDelayPassed = false;

private:
	float  m_delay;
	double m_time;
	double m_prevTime;
};
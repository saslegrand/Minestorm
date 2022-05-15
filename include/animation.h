#pragma once
#include <vector>

#include "particles.h"

class Animation
{
public:
	Animation() = default;
	~Animation() {}

	void draw() const;
	void update();

protected:
	std::vector<Particles> m_particles;
};
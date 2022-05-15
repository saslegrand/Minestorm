#pragma once
#include "movement.h"

class StaticMineMovement : public Movement
{
public:
	StaticMineMovement() = default;
	StaticMineMovement(float _maxSpeed, float _speed, float _drag);
	~StaticMineMovement() {}

	void updateAcceleration(Vector2D dir);
	void updateRotation(Referantial2D& localRef, float angle);
	void updatePosition(Referantial2D& localRef, float deltaTime);
};
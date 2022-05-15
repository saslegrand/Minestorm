#pragma once
#include "movement.h"

class PlayerMovement : public Movement
{
public:
	PlayerMovement() = default;
	PlayerMovement(float _maxSpeed, float _speed, float _drag);
	~PlayerMovement() {}

	void updateAcceleration(Referantial2D& localRef);
	void updateDeceleration(Referantial2D& localRef);
	void updateRotation(Referantial2D& localRef, float angle);
	void updatePosition(Referantial2D& localRef, float deltaTime);
};
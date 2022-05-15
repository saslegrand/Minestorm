#include "../include/static_mine_movement.h"
#include "../toolbox/maths.h"

StaticMineMovement::StaticMineMovement(float _maxSpeed, float _speed, float _drag)
{
	maxSpeed = _maxSpeed;
	speed    = _speed;
	drag     = _drag;
}

void StaticMineMovement::updateAcceleration(Vector2D dir)
{
	velocity = dir * maxSpeed;
}

void StaticMineMovement::updateRotation(Referantial2D& localRef, float angle)
{
	localRef.rotateRef(angle);
}

void StaticMineMovement::updatePosition(Referantial2D& localRef, float deltaTime)
{
	localRef.origin += velocity * deltaTime;
}
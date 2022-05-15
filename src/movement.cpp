#include "../include/Movement.h"
#include "../toolbox/maths.h"

/*Movement::Movement()
{
	maxSpeed = 0.f;
	speed	 = 0.f;
	drag	 = 0.f;
}

Movement::Movement(float _maxSpeed, float _speed, float _drag)
{
	maxSpeed = _maxSpeed;
	speed	 = _speed;
	drag	 = _drag;
}

void Movement::updateAcceleration(Referantial2D& localRef)
{
	if (velocity.squareLength() < maxSpeed * maxSpeed)
	{
		velocity += localRef.unitJ * speed;
	}
}
void Movement::updateDeceleration(Referantial2D& localRef)
{
	if (velocity.squareLength() > 0)
		velocity -= velocity * drag;

	velocity = localRef.global_to_local_vect(velocity);
	velocity.y = maths::clamp2f(velocity.y, 0.f, maxSpeed);
	velocity = localRef.local_to_global_vect(velocity);
}

void Movement::updateRotation(Referantial2D& localRef, float angle)
{
	localRef.rotateRef(angle);
}

void Movement::updatePosition(Referantial2D& localRef, float deltaTime)
{
	localRef.origin += velocity * deltaTime;
}*/
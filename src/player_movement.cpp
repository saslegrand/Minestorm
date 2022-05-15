#include "../include/player_movement.h"
#include "../toolbox/maths.h"

PlayerMovement::PlayerMovement(float _maxSpeed, float _speed, float _drag)
{
	maxSpeed = _maxSpeed;
	speed = _speed;
	drag = _drag;
}

void PlayerMovement::updateAcceleration(Referantial2D& localRef)
{
	// Increase velocity / clamp to maxSpeed
	if (velocity.squareLength() < maxSpeed * maxSpeed)
	{
		velocity += localRef.unitJ * speed;
	}
}

void PlayerMovement::updateDeceleration(Referantial2D& localRef)
{
	// Derease constantly velocity / clamp to 0
	if (velocity.squareLength() > 0)
		velocity -= velocity * drag;

	// Clamp the y velocity to 0 (from referantial of player)
	velocity = localRef.global_to_local_vect(velocity);
	velocity.y = maths::clamp2f(velocity.y, 0.f, maxSpeed);
	velocity = localRef.local_to_global_vect(velocity);
}

void PlayerMovement::updateRotation(Referantial2D& localRef, float angle)
{
	// Rotate the referantial from an angle
	localRef.rotateRef(angle);
}

void PlayerMovement::updatePosition(Referantial2D& localRef, float deltaTime)
{
	// Set the new position of the player
	localRef.origin += velocity * deltaTime;
}
#include <cmath>
#include <raylib.h>

#include "../toolbox/referantial2D.h"

Referantial2D::Referantial2D() 
{
	origin = { 0.f, 0.f };
	unitI  = { 1.f, 0.f };
	unitJ  = { 0.f, -1.f };
	angle  =   0.f;
}

Referantial2D::~Referantial2D() {}

void Referantial2D::reset()
{
	origin = { 0.f, 0.f };
	unitI = { 1.f, 0.f };
	unitJ = { 0.f, -1.f };
	angle = 0.f;
}

void Referantial2D::drawVectors() const
{
	DrawLine((int)origin.x, (int)origin.y, (int)origin.x + (int)(unitI.x * 40), (int)origin.y + (int)(unitI.y * 40), RED);
	DrawLine((int)origin.x, (int)origin.y, (int)origin.x + (int)(unitJ.x * 40), (int)origin.y + (int)(unitJ.y * 40), GREEN);
}

void Referantial2D::rotateRef(float _angle)
{
	unitI.rotateVector(_angle);
	unitJ.rotateVector(_angle);

	unitI = unitI.normalized();
	unitJ = unitJ.normalized();

	angle += _angle;
}

void Referantial2D::init_ref(Vector2D o)
{
	origin  = o;
	angle = 0.f;
	unitI = { 1.f, 0.f };
	unitJ = { 0.f, -1.f };
}

Vector2D Referantial2D::local_to_global(Referantial2D global, Vector2D localPos)
{
	return ((this->origin - global.origin) + local_to_global_vect(localPos));
}

Vector2D Referantial2D::global_to_local(Vector2D globalPos)
{
	return global_to_local_vect(globalPos - this->origin);
}

Vector2D Referantial2D::local_to_global_vect(Vector2D localPos)
{
	return ((this->unitI * localPos.x) + (this->unitJ * localPos.y));
}

Vector2D Referantial2D::global_to_local_vect(Vector2D globalPos)
{
	return { globalPos.dotProduct(this->unitI), globalPos.dotProduct(this->unitJ) };
}
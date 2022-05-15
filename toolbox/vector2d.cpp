#include "vector2d.h"

Vector2D::Vector2D()
{
	x = 0.f;
	y = 0.f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D::~Vector2D()
{

}

// dot product
float Vector2D::operator*(const Vector2D vect) const
{
	return (this->x * vect.x + this->y * vect.y);
}

// scale
Vector2D Vector2D::operator*(float scale) const
{
    return {this->x * scale, this->y * scale};
}

// dot product
float Vector2D::operator*=(Vector2D vect) const
{
    return (this->x * vect.x + this->y * vect.y);
}

// scale
Vector2D Vector2D::operator*=(float scale)
{
	x *= scale;
	y *= scale;

	return *this;
}

// soustraction vectors
Vector2D Vector2D::operator-(const Vector2D vect) const
{
    return {this->x - vect.x, this->y - vect.y};
}

// soustraction vectors
Vector2D Vector2D::operator-=(const Vector2D vect)
{
    x -= vect.x;
    y -= vect.y;

    return *this;
}

// addition vectors
Vector2D Vector2D::operator+(const Vector2D vect) const
{
    return {this->x + vect.x, this->y + vect.y};
}

// addition vectors
Vector2D Vector2D::operator+=(const Vector2D vect)
{
    x += vect.x;  
    y += vect.y;  
    
    return *this;
}

Vector2D Vector2D::normalized() const 
{
    float mag = this->length();
    if (mag == 0)
        return nullVect();
    
    Vector2D vect {this->x / mag, this->y / mag};
    return vect;
}

Vector2D Vector2D::negateVector() const
{
    return {this->x * -1.f, this->y * -1.f};
}

bool Vector2D::compareValue(const Vector2D vect, float value) const
{
    return (fabsf(this->x - vect.x) < value && fabsf(this->y - vect.y < value));
}

float Vector2D::distanceVectors(const Vector2D vect) const
{
    return (*this - vect).length();
}

float Vector2D::angleVectors(const Vector2D vect) const
{
    float magVect = this->length() * vect.length();

    if (magVect == 0.f)
        return 0.f;

    return acosf((*this * vect) / magVect);
}

Vector2D Vector2D::rotateVector(float angle)
{
    Vector2D rotVect;

    rotVect.x = this->x * cosf(angle) - this->y * sinf(angle);
    rotVect.y = this->x * sinf(angle) + this->y * cosf(angle);
    *this = rotVect;

    return *this;
}

Vector2D Vector2D::rotateCenterVector(const Vector2D center, float angle)
{
    return (*this - center).rotateVector(angle) + center;
}

Vector2D Vector2D::rotatePerpendicular() const
{
    return {- this->y, this->x};
}

Vector2D Vector2D::rotatePerpendicular()
{
    float temp = this->x;
    this->x = - this->y;
    this->y = temp;

    return *this;
}

Vector2D Vector2D::normalVector()
{
    Vector2D vect = *this;
    return (vect.normalized()).rotatePerpendicular();
}

bool Vector2D::operator==(const Vector2D target)
{
    return (this->x == target.x && this->y == target.y);
}
#pragma once
#include <raylib.h>
#include <math.h>

class Vector2D
{
    public:
    	Vector2D();
    	Vector2D(float, float);
    	~Vector2D();

        Vector2  toVector2() const { return { x, y }; }
    	float    operator*(const Vector2D) const;
        float    operator*=(const Vector2D) const;
        Vector2D operator*(float) const;
    	Vector2D operator*=(float);
        Vector2D operator-(const Vector2D) const;
        Vector2D operator-=(const Vector2D);
        Vector2D operator+(const Vector2D) const;
        Vector2D operator+=(const Vector2D);
        bool     operator==(const Vector2D);

        float    dotProduct(Vector2D v2) const { return (this->x * v2.x + this->y * v2.y); };
        Vector2D nullVect() const { Vector2D vect {0, 0}; return vect; }
        Vector2D normalized() const;
        Vector2D negateVector() const;
        Vector2D rotateVector(float);
        Vector2D rotateCenterVector(const Vector2D, float);
        Vector2D rotatePerpendicular() const;
        Vector2D rotatePerpendicular();
        Vector2D normalVector();
        bool     compareValue(const Vector2D, float) const;
        float    distanceVectors(const Vector2D) const;
        float    angleVectors(const Vector2D) const;
        float    squareLength() const { return this->x * this->x + this->y * this->y; }
        float    length() const { return sqrtf(this->squareLength()); }

    	float    x;
    	float    y;
};

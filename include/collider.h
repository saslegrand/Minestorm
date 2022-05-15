#pragma once
#include <vector>

#include "../toolbox/convexPolygon.h"
#include "../toolbox/referantial2d.h"

class Collider
{
public:
	Collider(){}
	~Collider() { shapes.clear(); }

	void addShape(std::vector<Vector2D> shape, int nbPoint);
	void updateShapesRotation(Vector2D origin, float angle);
	void updateShapesPosition(Vector2D velocity, float deltaTime);
	void updateAABB();

	void drawShapesAABB() const;

	std::vector<ConvexPolygon> shapes;
	AABB					   aabb;
};
#include "../include/collider.h"

void Collider::addShape(std::vector<Vector2D> shape, int nbPoint)
{
	shapes.push_back({ nbPoint, shape });
}

void Collider::updateShapesRotation(Vector2D origin, float angle)
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		for (unsigned int j = 0; j < shapes[i].pointsList.size(); j++)
		{
			shapes[i].pointsList[j] = shapes[i].pointsList[j].rotateCenterVector(origin, angle);
		}
	}
}

void Collider::updateShapesPosition(Vector2D velocity, float deltaTime)
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		for (unsigned int j = 0; j < shapes[i].pointsList.size(); j++)
		{
			shapes[i].pointsList[j] += velocity * deltaTime;
		}
	}
}

void Collider::updateAABB()
{
	aabb.resetMinMax();

	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		shapes[i].AABB.resetMinMax();

		for (unsigned int j = 0; j < shapes[i].pointsList.size(); j++)
		{
			Vector2D curPoint = shapes[i].pointsList[j];

			shapes[i].AABB.update(curPoint.x, curPoint.y);
			aabb.update(curPoint.x, curPoint.y);
		}
	}
}

void drawShapes(const std::vector<ConvexPolygon>& shapes)
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		for (unsigned int j = 0; j < shapes[i].pointsList.size(); j++)
		{
			DrawLine((int)shapes[i].pointsList[j].x, (int)shapes[i].pointsList[j].y,
				(int)shapes[i].pointsList[(j + 1) % (int)shapes[i].pointsList.size()].x,
				(int)shapes[i].pointsList[(j + 1) % (int)shapes[i].pointsList.size()].y, shapes[i].color);
		}
	}
}

void drawAABB(const AABB& entityAABB, const std::vector<ConvexPolygon>& shapes)
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		shapes[i].AABB.draw();
	}

	entityAABB.draw();
}

void Collider::drawShapesAABB() const
{
	drawShapes(shapes);
	drawAABB(aabb, shapes);
}
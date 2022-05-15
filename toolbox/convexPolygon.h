#pragma once
#include <vector>
#include <raylib.h>

#include "vector2d.h"
#include "AABB.h"

class ConvexPolygon
{
public:
    ConvexPolygon() {}
    ConvexPolygon(int, std::vector<Vector2D>&);
    ~ConvexPolygon() {}

    void init(int nb, std::vector<Vector2D>& ptList) { this->nbPoint = nb; this->pointsList = ptList; }

    int   nbPoint = 0;
    AABB  AABB;
    Color color = WHITE;

    std::vector<Vector2D> pointsList;
};
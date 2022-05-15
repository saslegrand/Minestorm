#include "convexPolygon.h"

ConvexPolygon::ConvexPolygon(int _nbPoint, std::vector<Vector2D>& _listPoints)
{
    nbPoint = _nbPoint;
    pointsList = _listPoints;
}
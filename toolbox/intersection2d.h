#pragma once

#include "vector2d.h"
#include "convexPolygon.h"
#include "range.h"
#include "circle2d.h"
#include "AABB.h"


bool convPol_point_intersect(const ConvexPolygon&, const Vector2D&);
bool convPol_convPol_intersect(const ConvexPolygon& cp1, const ConvexPolygon& cp2);
bool convPol_circle_intersect(const Circle2D& circle, const ConvexPolygon& cp);

bool circles_intersect(const Circle2D& circle1, const Circle2D& circle2);
bool circle_box_intersect(const Circle2D& circle, const AABB& box);
bool box_box_intersect(const AABB& box1, const AABB& box2);
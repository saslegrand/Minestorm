#include "intersection2d.h"
#include "maths.h"

// Collision between two convex polygons
bool convPol_point_intersect(const ConvexPolygon& cp, const Vector2D& pt)
{
    for (int i = 0; i < cp.nbPoint; i++)
    {
        Vector2D norm = (cp.pointsList[(i + 1) % cp.nbPoint] - cp.pointsList[i]).normalVector();
        Range convPol = { cp.pointsList[0].dotProduct(norm), cp.pointsList[0].dotProduct(norm) };
        Range ptRange = pt.dotProduct(norm);

        // Update convex polyon range
        for (int i = 1; i < cp.nbPoint; i++)
        {
            // Project points from the normal of polygon segments
            convPol = convPol.valueInRange(cp.pointsList[i].dotProduct(norm));
        }

        if (!(ptRange.intersectRange(convPol)))
        {
            return false;
        }
    }

    return true;
}

// Check if there is a separator axe between two polygons
bool isSeparatorAxe(const ConvexPolygon& cp1, const ConvexPolygon& cp2)
{
    for (int i = 0; i < cp1.nbPoint; i++)
    {
        Vector2D norm = (cp1.pointsList[(i + 1) % cp1.nbPoint] - cp1.pointsList[i]).normalVector();
        Range convPol1 = { cp1.pointsList[0].dotProduct(norm), cp1.pointsList[0].dotProduct(norm) };
        Range convPol2 = { cp2.pointsList[0].dotProduct(norm), cp2.pointsList[0].dotProduct(norm) };

        // Update convex polyon ranges
        for (int j = 1; j < cp1.nbPoint; j++)
        {
            // Project points from the normal of polygon segments
            convPol1 = convPol1.valueInRange(cp1.pointsList[j].dotProduct(norm));
        }

        for (int k = 1; k < cp2.nbPoint; k++)
        {
            // Project points from the normal of polygon segments
            convPol2 = convPol2.valueInRange(cp2.pointsList[k].dotProduct(norm));
        }

        if (!convPol1.intersectRange(convPol2))
        {
            return false;
        }
    }

    return true;
}

// Collision between two convex polygons
bool convPol_convPol_intersect(const ConvexPolygon& cp1, const ConvexPolygon& cp2)
{
    return (isSeparatorAxe(cp1, cp2) && isSeparatorAxe(cp2, cp1));
}

// Collision between convex polygon and circle
bool convPol_circle_intersect(const Circle2D& circle, const ConvexPolygon& cp)
{
    Vector2D summit = cp.pointsList[0];
    Vector2D normCircle, scaleNorm;
    Range    circleRange, cpRange;

    // Check if ranges intersect (project points on polygon normals)
    for (int i = 0; i < cp.nbPoint; i++)
    {
        Vector2D norm = (cp.pointsList[(i + 1) % cp.nbPoint] - cp.pointsList[i]).normalVector();
        scaleNorm = norm * circle.radius;
        circleRange = { (circle.center - scaleNorm).dotProduct(norm), (circle.center + scaleNorm).dotProduct(norm) };
        cpRange = { cp.pointsList[0].dotProduct(norm), cp.pointsList[0].dotProduct(norm) };

        // Update convex polygon range and get the neraest summit from the center of the circle
        for (int j = 1; j < cp.nbPoint; j++)
        {
            cpRange = cpRange.valueInRange(cp.pointsList[j].dotProduct(norm));

            if ((cp.pointsList[j] - circle.center).squareLength() < (summit - circle.center).squareLength())
                summit = cp.pointsList[j];
        }

        if (!cpRange.intersectRange(circleRange))
            return false;
    }

    // Check if ranges intersect (project point on circle normal)
    normCircle = (circle.center - summit).normalized();
    scaleNorm = normCircle * circle.radius;
    circleRange = { (circle.center - scaleNorm).dotProduct(normCircle), (circle.center + scaleNorm).dotProduct(normCircle) };
    cpRange = { cp.pointsList[0].dotProduct(normCircle), cp.pointsList[0].dotProduct(normCircle) };

    // Update convex polyon range
    for (int i = 1; i < cp.nbPoint; i++)
    {
        cpRange = cpRange.valueInRange(cp.pointsList[i].dotProduct(normCircle));
    }

    // Check if there is an intersection
    if (!cpRange.intersectRange(circleRange))
        return false;

    return true;
}

// Collision between circle and box
bool circle_box_intersect(const Circle2D& circle, const AABB& box)
{
    float    boxHalfWidth = box.width / 2.f;
    float    boxHalfHeight = box.height / 2.f;

    if (fabsf(circle.center.x - (box.pos.x + box.center.x)) <= boxHalfWidth
        && fabsf(circle.center.y - (box.pos.y + box.center.y)) <= boxHalfHeight)
        return true;

    Vector2D pointBox;
    pointBox.x = maths::clamp2f(circle.center.x, box.center.x - boxHalfWidth, box.center.x + boxHalfWidth);
    pointBox.y = maths::clamp2f(circle.center.y, box.center.y - boxHalfHeight, box.center.y + boxHalfHeight);

    return ((circle.center - pointBox).squareLength() <= powf(circle.radius, 2.f));
}

// COllision between two boxes
bool box_box_intersect(const AABB& box1, const AABB& box2)
{
    float box1HalfWidth  = box1.width * 0.5f;
    float box1HalfHeight = box1.height * 0.5f;
    float box2HalfWidth  = box2.width * 0.5f;
    float box2HalfHeight = box2.height * 0.5f;

    Range rangeBox1X = { box1.center.x - box1HalfWidth, box1.center.x + box1HalfWidth };
    Range rangeBox1Y = { box1.center.y - box1HalfHeight, box1.center.y + box1HalfHeight };

    Range rangeBox2X = { box2.center.x - box2HalfWidth, box2.center.x + box2HalfWidth };
    Range rangeBox2Y = { box2.center.y - box2HalfHeight, box2.center.y + box2HalfHeight };

    return (rangeBox1X.intersectRange(rangeBox2X) && rangeBox1Y.intersectRange(rangeBox2Y));
}

// COllision between two circles
bool circles_intersect(const Circle2D& circle1, const Circle2D& circle2)
{
    float circlesRadius = circle1.radius + circle2.radius;
    return ((circle1.center - circle2.center).squareLength() <= (circlesRadius * circlesRadius));
}
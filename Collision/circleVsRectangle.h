
#ifndef CIRCLE_VS_RECTANGLE_H
#define CIRCLE_VS_RECTANGLE_H

#include <algorithm>
#include <cmath>

#include "../body.h"
#include "../circle.h"
#include "../rectangle.h"
#include "collisionManifold.h"

collisionManifold circleVsRectangle(
    const Body& circleBody,
    const Body& rectBody
) {
    collisionManifold manifold{};

    const Circle* circle =
        dynamic_cast<const Circle*>(circleBody.shape.get());

    const Rectangle* rectangle =
        dynamic_cast<const Rectangle*>(rectBody.shape.get());

    if (!circle || !rectangle) {
        return manifold;
    }

    float minX = rectBody.position.x - rectangle->width / 2.0f;
    float maxX = rectBody.position.x + rectangle->width / 2.0f;

    float minY = rectBody.position.y - rectangle->height / 2.0f;
    float maxY = rectBody.position.y + rectangle->height / 2.0f;

    // Find closest point on rectangle.
    float closestX = std::clamp(
        circleBody.position.x, minX, maxX
    );

    float closestY = std::clamp(
        circleBody.position.y, minY, maxY
    );

    Vec2 closestPoint(closestX, closestY);

    // Direction from circle center to closest point.
    Vec2 difference = closestPoint - circleBody.position;

    float distanceSquared = difference.magSquared();
    float radiusSquared = circle->radius * circle->radius;

    if (distanceSquared > radiusSquared) {
        return manifold;
    }

    // Circle center is inside the rectangle
    // or exactly on its boundary.
    if (distanceSquared < 1e-12f) {

        float leftDistance = circleBody.position.x - minX;
        float rightDistance = maxX - circleBody.position.x;

        float bottomDistance = circleBody.position.y - minY;
        float topDistance = maxY - circleBody.position.y;

        float minDistance = std::min({
            leftDistance,
            rightDistance,
            bottomDistance,
            topDistance
        });

        if (minDistance == leftDistance) {
            manifold.normal = Vec2(1, 0);
            manifold.contactPoint =
                Vec2(minX, circleBody.position.y);
        }
        else if (minDistance == rightDistance) {
            manifold.normal = Vec2(-1, 0);
            manifold.contactPoint =
                Vec2(maxX, circleBody.position.y);
        }
        else if (minDistance == bottomDistance) {
            manifold.normal = Vec2(0, 1);
            manifold.contactPoint =
                Vec2(circleBody.position.x, minY);
        }
        else {
            manifold.normal = Vec2(0, -1);
            manifold.contactPoint =
                Vec2(circleBody.position.x, maxY);
        }

        manifold.penetration = circle->radius + minDistance;
    }
    else {

        float distance = std::sqrt(distanceSquared);

        manifold.normal = difference / distance;
        manifold.penetration = circle->radius - distance;
        manifold.contactPoint = closestPoint;
    }

    manifold.colliding = true;

    return manifold;
}

#endif

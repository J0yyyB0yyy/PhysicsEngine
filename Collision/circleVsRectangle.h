
#ifndef CIRCLE_VS_RECTANGLE_H
#define CIRCLE_VS_RECTANGLE_H

#include <algorithm>
#include "../body.h"
#include "../circle.h"
#include "../rectangle.h"
#include "collisionManifold.h"

collisionManifold circleVsRectangle(
    const Body& circleBody,
    const Body& rectBody
) {
    collisionManifold manifold{};

    const Circle* circle = dynamic_cast<const Circle*>(circleBody.shape.get());
    const Rectangle* rectangle = dynamic_cast<const Rectangle*>(rectBody.shape.get());

    if (!circle || !rectangle) {
        return manifold;
    }

    float minX = rectBody.position.x - rectangle->width / 2.0f;
    float maxX = rectBody.position.x + rectangle->width / 2.0f;

    float minY = rectBody.position.y - rectangle->height / 2.0f;
    float maxY = rectBody.position.y + rectangle->height / 2.0f;

    float closestX = std::clamp(
        circleBody.position.x, minX, maxX
    );

    float closestY = std::clamp(
        circleBody.position.y, minY, maxY
    );

    Vec2 closestPoint(closestX, closestY);

    Vec2 difference = closestPoint - circleBody.position;

    float distanceSquared = difference.magSquared();
    float radiusSquared = circle->radius * circle->radius;

    if (distanceSquared > radiusSquared) {
        return manifold;
    }
    if (distanceSquared > 1e-6f) {

        float distance = std::sqrt(distanceSquared);

        manifold.normal = difference / distance;
        manifold.penetration = circle->radius - distance;
        manifold.contactPoint = closestPoint;
    }
    else {

        float left = circleBody.position.x - minX;
        float right = maxX - circleBody.position.x;

        float bottom = circleBody.position.y - minY;
        float top = maxY - circleBody.position.y;

        float nearest = left;

        manifold.normal = Vec2(-1, 0);
        manifold.contactPoint = Vec2(minX, circleBody.position.y);

        if (right < nearest) {
            nearest = right;
            manifold.normal = Vec2(1, 0);
            manifold.contactPoint = Vec2(maxX, circleBody.position.y);
        }

        if (bottom < nearest) {
            nearest = bottom;
            manifold.normal = Vec2(0, -1);
            manifold.contactPoint = Vec2(circleBody.position.x, minY);
        }

        if (top < nearest) {
            nearest = top;
            manifold.normal = Vec2(0, 1);
            manifold.contactPoint = Vec2(circleBody.position.x, maxY);
        }

        manifold.penetration = circle->radius + nearest;
    }

    manifold.colliding = true;

    return manifold;
}

#endif

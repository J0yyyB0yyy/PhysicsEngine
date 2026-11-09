
#ifndef RECTANGLE_VS_RECTANGLE_H
#define RECTANGLE_VS_RECTANGLE_H

#include <algorithm>
#include "../body.h"
#include "../rectangle.h"
#include "collisionManifold.h"

inline collisionManifold rectangleVsRectangle(
    const Body& a,
    const Body& b
) {
    collisionManifold manifold{};

    const Rectangle* rectA =
        dynamic_cast<const Rectangle*>(a.shape.get());

    const Rectangle* rectB =
        dynamic_cast<const Rectangle*>(b.shape.get());

    if (!rectA || !rectB) {
        return manifold;
    }

    float aMinX = a.position.x - rectA->width / 2.0f;
    float aMaxX = a.position.x + rectA->width / 2.0f;

    float aMinY = a.position.y - rectA->height / 2.0f;
    float aMaxY = a.position.y + rectA->height / 2.0f;

    float bMinX = b.position.x - rectB->width / 2.0f;
    float bMaxX = b.position.x + rectB->width / 2.0f;

    float bMinY = b.position.y - rectB->height / 2.0f;
    float bMaxY = b.position.y + rectB->height / 2.0f;

    float overlapX =
        std::min(aMaxX, bMaxX) - std::max(aMinX, bMinX);

    float overlapY =
        std::min(aMaxY, bMaxY) - std::max(aMinY, bMinY);

    // Exact contact is a collision, matching the other shape pairs.
    if (overlapX < 0.0f || overlapY < 0.0f) {
        return manifold;
    }

    // Select the axis with minimum penetration.
    if (overlapX < overlapY) {

        manifold.normal = Vec2(
            b.position.x >= a.position.x ? 1.0f : -1.0f,
            0.0f
        );

        manifold.penetration = overlapX;

    } else {

        manifold.normal = Vec2(
            0.0f,
            b.position.y >= a.position.y ? 1.0f : -1.0f
        );

        manifold.penetration = overlapY;
    }

    // Approximate contact point.
    float contactX = (
        std::max(aMinX, bMinX) +
        std::min(aMaxX, bMaxX)
    ) / 2.0f;

    float contactY = (
        std::max(aMinY, bMinY) +
        std::min(aMaxY, bMaxY)
    ) / 2.0f;

    manifold.contactPoint = Vec2(contactX, contactY);

    manifold.colliding = true;

    return manifold;
}

#endif

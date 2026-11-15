
#ifndef CIRCLE_VS_RECTANGLE_H
#define CIRCLE_VS_RECTANGLE_H

#include <algorithm>
#include "body.h"
#include "circle.h"
#include "rectangle.h"

bool circleVsRectangle(const Body& circleBody, const Body& rectBody) {

    const Circle* circle =
        dynamic_cast<const Circle*>(circleBody.shape.get());

    const Rectangle* rectangle =
        dynamic_cast<const Rectangle*>(rectBody.shape.get());

    if (circle == nullptr || rectangle == nullptr) {
        return false;
    }

    float halfWidth = rectangle->width / 2.0f;
    float halfHeight = rectangle->height / 2.0f;

    float minX = rectBody.position.x - halfWidth;
    float maxX = rectBody.position.x + halfWidth;

    float minY = rectBody.position.y - halfHeight;
    float maxY = rectBody.position.y + halfHeight;

    float closestX = std::clamp(
        circleBody.position.x, minX, maxX
    );

    float closestY = std::clamp(
        circleBody.position.y, minY, maxY
    );

    Vec2 closestPoint(closestX, closestY);

    Vec2 difference = circleBody.position - closestPoint;

    return difference.magSquared() <= circle->radius * circle->radius;
}

#endif

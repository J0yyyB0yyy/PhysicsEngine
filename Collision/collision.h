
#ifndef COLLISION_H
#define COLLISION_H

#include "../body.h"
#include "collisionManifold.h"
#include "circleVsCircle.h"
#include "rectangleVsRectangle.h"
#include "circleVsRectangle.h"

collisionManifold checkCollision(
    const Body& a,
    const Body& b
) {

    collisionManifold manifold{};

    if (!a.shape || !b.shape) {
        return manifold;
    }

    ShapeType typeA = a.shape->getType();
    ShapeType typeB = b.shape->getType();

    // Circle vs Circle
    if (typeA == ShapeType::Circle &&
        typeB == ShapeType::Circle) {

        return circleVsCircle(a, b);
    }

    // Rectangle vs Rectangle
    if (typeA == ShapeType::Rectangle &&
        typeB == ShapeType::Rectangle) {

        return rectangleVsRectangle(a, b);
    }

    // Circle vs Rectangle
    if (typeA == ShapeType::Circle &&
        typeB == ShapeType::Rectangle) {

        return circleVsRectangle(a, b);
    }

    // Rectangle vs Circle
    if (typeA == ShapeType::Rectangle &&
        typeB == ShapeType::Circle) {

        manifold = circleVsRectangle(b, a);

        // Reverse normal because argument order changed.
        manifold.normal = manifold.normal * -1.0f;

        return manifold;
    }

    return manifold;
}

#endif

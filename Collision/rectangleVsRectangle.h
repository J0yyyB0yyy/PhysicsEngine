
#ifndef RECTANGLE_VS_RECTANGLE_H
#define RECTANGLE_VS_RECTANGLE_H

#include "rectangle.h"
#include "body.h"

bool rectangleVsRectangle(
    const Body& a,
    const Body& b
) {
    const Rectangle* rectA =
        static_cast<const Rectangle*>(a.shape.get());

    const Rectangle* rectB =
        static_cast<const Rectangle*>(b.shape.get());

    float aMinX = a.position.x - rectA->width / 2.0f;
    float aMaxX = a.position.x + rectA->width / 2.0f;

    float aMinY = a.position.y - rectA->height / 2.0f;
    float aMaxY = a.position.y + rectA->height / 2.0f;

    float bMinX = b.position.x - rectB->width / 2.0f;
    float bMaxX = b.position.x + rectB->width / 2.0f;

    float bMinY = b.position.y - rectB->height / 2.0f;
    float bMaxY = b.position.y + rectB->height / 2.0f;

    if (aMaxX < bMinX ||
        aMinX > bMaxX ||
        aMaxY < bMinY ||
        aMinY > bMaxY) {

        return false;
    }

    return true;
}

#endif

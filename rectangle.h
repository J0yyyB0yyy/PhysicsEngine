#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    float width;
    float height;

    Rectangle(float width, float height)
        : width(width), height(height) {
    }
};

#endif
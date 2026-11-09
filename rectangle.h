#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include <stdexcept>

class Rectangle : public Shape {
public:
    float width;
    float height;

    Rectangle(float width, float height)
        : width(width), height(height) {
        if (!(width > 0.0f) || !(height > 0.0f)) {
            throw std::invalid_argument("Rectangle dimensions must be positive");
        }
    }
    ShapeType getType() const override{
        return ShapeType::Rectangle;
    }
};

#endif

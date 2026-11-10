#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <stdexcept>

class Circle : public Shape {
public:
    float radius;

    Circle(float radius)
        : radius(radius) {
        if (!(radius > 0.0f)) {
            throw std::invalid_argument("Circle radius must be positive");
        }
    }
    ShapeType getType() const override{
        return ShapeType::Circle;
    }
};



#endif

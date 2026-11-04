#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
public:
    float radius;

    Circle(float radius)
        : radius(radius) {
    }
    ShapeType getType() const override{
        return ShapeType::Circle;
    }
};



#endif
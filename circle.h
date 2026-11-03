#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
public:
    float radius;

    Circle(float radius)
        : radius(radius) {
    }
};



#endif
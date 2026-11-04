#ifndef COLLISION_H
#define COLLISION_H

#include"circleVsCircle.h"
#include"circleVsRectangle.h"
#include"rectangleVsRectangle.h"

bool checkCollision(const Body& a, const Body& b){
    ShapeType typeA = a.shape->getType();
    ShapeType typeB = a.shape->getType();

    if(typeA == ShapeType::Circle && typeB == ShapeType::Circle){
        return circleVsCircle(a, b);
    }
}

#endif
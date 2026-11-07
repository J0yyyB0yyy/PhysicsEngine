#ifndef COLLISION_H
#define COLLISION_H

#include "../body.h"
#include "circleVsCircle.h"
#include "rectangleVsRectangle.h"
#include "circleVsRectangle.h"
#include "collisionManifold.h"


bool checkCollision(const Body& a, const Body& b) {

    if (!a.shape || !b.shape)
        return false;

<<<<<<< HEAD
bool checkCollision(const Body& a, const Body& b){
	ShapeType typeA = a.shape->getType();
    	ShapeType typeB = a.shape->getType();

    	if(typeA == ShapeType::Circle && typeB == ShapeType::Circle){
        	return circleVsCircle(a, b);
    	}
	if(typeA == ShapeType::Circle && typeB == ShapeType::Rectangle){
	   return circleVsRectangle(a, b);
    	}

	if(typeA == ShapeType::Rectangle && typeB == ShapeType::Rectangle){
        	return rectangleVsRectangle(a, b);
	}
=======
    ShapeType typeA = a.shape->getType();
    ShapeType typeB = b.shape->getType();

    if (typeA == ShapeType::Circle &&
        typeB == ShapeType::Circle) {

        return circleVsCircle(a, b).colliding;
    }

    if (typeA == ShapeType::Rectangle &&
        typeB == ShapeType::Rectangle) {

        return rectangleVsRectangle(a, b).colliding;
    }

    if (typeA == ShapeType::Circle &&
        typeB == ShapeType::Rectangle) {

        return circleVsRectangle(a, b).colliding;
    }

    if (typeA == ShapeType::Rectangle &&
        typeB == ShapeType::Circle) {

        return circleVsRectangle(b, a).colliding;
    }

    return false;
>>>>>>> 3cdb32f (Made collision system better)
}

#endif

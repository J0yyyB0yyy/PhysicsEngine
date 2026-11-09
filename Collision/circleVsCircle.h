#ifndef CIRCLE_VS_CIRCLE_H
#define CIRCLE_VS_CIRCLE_H


#include "../body.h"
#include "../circle.h"
#include "collisionManifold.h"



inline collisionManifold circleVsCircle(const Body& a, const Body& b){

    collisionManifold manifold{};
    manifold.colliding = false;

    const Circle* circleA = dynamic_cast<const Circle*>(a.shape.get());
    const Circle* circleB = dynamic_cast<const Circle*>(b.shape.get());

    if(circleA == nullptr || circleB == nullptr){
        return manifold;
    }

    Vec2 dist = (b.position - a.position);
    float radiusSum = circleA->radius + circleB->radius;
    if (dist.magSquared() > radiusSum * radiusSum) {
        return manifold;
    }

    float distance = dist.mag();

    if (distance > 0.0f) {
        manifold.normal = dist / distance;
    } else {
        manifold.normal = Vec2(1, 0);
    }

    manifold.penetration = radiusSum - distance;

    manifold.contactPoint = a.position + manifold.normal * circleA->radius;

    manifold.colliding = true;

    return manifold;
   
}

#endif

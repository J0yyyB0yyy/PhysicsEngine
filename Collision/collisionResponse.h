#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

#include "collisionManifold.h"
#include "../body.h"
#include <algorithm>

void positionalCorrection(Body& a, Body& b, const collisionManifold& manifold){

    if(!manifold.colliding){
        return;
    }

    float invMassSum = a.inverseMass + b.inverseMass;
    if (invMassSum == 0.0f) return;

    const float slop = 0.01f;
    const float percent = 0.8f;

    float correctionMagnitude = std::max(manifold.penetration - slop, 0.0f)*percent / invMassSum;
    Vec2 correction = manifold.normal * correctionMagnitude;

    a.position -= a.inverseMass*correction;
    b.position += b.inverseMass*correction;
}

void resolveCollision(Body& a, Body& b, const collisionManifold& manifold){
    if (!manifold.colliding) return;

    Vec2 relativeVelocity = b.velocity - a.velocity;
    float velocityAlongNormal = relativeVelocity.dot(manifold.normal);
    if (velocityAlongNormal > 0) {
        return;
    }

    float e = std::min(a.restitution, b.restitution);

    float invMassSum = a.inverseMass + b.inverseMass;
    if (invMassSum == 0.0f) {
        return;
    }

    float impulse = -(1.0f+e)*(velocityAlongNormal)/(invMassSum);
    Vec2 impulseVector = impulse*manifold.normal;

    a.velocity -= a.inverseMass*impulseVector;
    b.velocity += b.inverseMass*impulseVector;
}

void friction(Body& a, Body& b, const collisionManifold& manifold){
    if(!manifold.colliding) return;

    float invMassSum = a.inverseMass + b.inverseMass;
    if(invMassSum == 0.0f) return ;
    float e = std::min(a.restitution, b.restitution);
    Vec2 relativeVelocity = b.velocity - a.velocity;

    Vec2 tangent = Vec2(-manifold.normal.y, manifold.normal.x);
    float velocityAlongTangent = relativeVelocity.dot(tangent);

    float impulse = -(1.0f)*velocityAlongTangent/(invMassSum);
    Vec2 impulseVector = impulse*tangent;
    

}
#endif

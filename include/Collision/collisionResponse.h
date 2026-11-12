#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

#include "collisionManifold.h"
#include "../Physics/body.h"
#include <algorithm>
#include <cmath>

inline void positionalCorrection(Body& a, Body& b, const collisionManifold& manifold) {
    if (!manifold.colliding) return;

    const float invMassSum = a.inverseMass + b.inverseMass;
    if (invMassSum <= 0.0f) return;

    constexpr float slop = 0.01f;
    constexpr float percent = 0.8f;
    const float magnitude = std::max(manifold.penetration - slop, 0.0f) * percent / invMassSum;
    const Vec2 correction = manifold.normal * magnitude;
    a.position -= a.inverseMass * correction;
    b.position += b.inverseMass * correction;
}

inline void friction(Body& a, Body& b, const collisionManifold& manifold, float normalImpulse) {
    const float invMassSum = a.inverseMass + b.inverseMass;
    if (!manifold.colliding || invMassSum <= 0.0f || normalImpulse <= 0.0f) return;

    const Vec2 relativeVelocity = b.velocity - a.velocity;
    const Vec2 tangent(-manifold.normal.y, manifold.normal.x);
    const float tangentSpeed = relativeVelocity.dot(tangent);
    float tangentImpulse = -tangentSpeed / invMassSum;
    const float coefficient = std::sqrt(std::max(0.0f, a.friction * b.friction));
    const float limit = coefficient * normalImpulse;
    tangentImpulse = std::clamp(tangentImpulse, -limit, limit);

    const Vec2 impulse = tangentImpulse * tangent;
    a.velocity -= a.inverseMass * impulse;
    b.velocity += b.inverseMass * impulse;
}

inline void resolveCollision(Body& a, Body& b, const collisionManifold& manifold) {
    if (!manifold.colliding) return;

    const float invMassSum = a.inverseMass + b.inverseMass;
    if (invMassSum <= 0.0f) return;

    const Vec2 relativeVelocity = b.velocity - a.velocity;
    const float velocityAlongNormal = relativeVelocity.dot(manifold.normal);
    if (velocityAlongNormal >= 0.0f) return;

    const float restitution = std::clamp(std::min(a.restitution, b.restitution), 0.0f, 1.0f);
    const float impulseMagnitude = -(1.0f + restitution) * velocityAlongNormal / invMassSum;
    const Vec2 impulse = impulseMagnitude * manifold.normal;
    a.velocity -= a.inverseMass * impulse;
    b.velocity += b.inverseMass * impulse;
    friction(a, b, manifold, impulseMagnitude);
}

#endif

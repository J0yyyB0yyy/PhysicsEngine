#ifndef COLLISION_MANIFOLD_H
#define COLLISION_MANIFOLD_H

#include "../vec2.h"

struct collisionManifold {
    Vec2 normal{};
    float penetration = 0.0f;
    Vec2 contactPoint{};
    bool colliding = false;
};

#endif

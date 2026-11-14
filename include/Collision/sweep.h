#ifndef SWEEP_H
#define SWEEP_H

#include <algorithm>
#include <cmath>
#include <utility>

#include "../Physics/body.h"
#include "../Physics/rectangle.h"
#include "../Physics/vec2.h"

inline bool sweepCircleVsRect(Vec2 start, Vec2 delta, float r,const Body& rect, const Rectangle& shape, float& toi, Vec2& normal) {
    float minX = rect.position.x - shape.width  / 2 - r;
    float maxX = rect.position.x + shape.width  / 2 + r;
    float minY = rect.position.y - shape.height / 2 - r;
    float maxY = rect.position.y + shape.height / 2 + r;

    float tmin = 0.0f, tmax = 1.0f;
    Vec2 n(0, 0);

    auto slab = [&](float s, float d, float lo, float hi, Vec2 loN, Vec2 hiN) {
        if (std::fabs(d) < 1e-8f) return s >= lo && s <= hi;
        float t1 = (lo - s) / d, t2 = (hi - s) / d;
        Vec2 entry = loN;
        if (t1 > t2) { std::swap(t1, t2); entry = hiN; }
        if (t1 > tmin) { tmin = t1; n = entry; }
        tmax = std::min(tmax, t2);
        return tmin <= tmax;
    };

    if (!slab(start.x, delta.x, minX, maxX, Vec2(-1, 0), Vec2(1, 0))) return false;
    if (!slab(start.y, delta.y, minY, maxY, Vec2(0, -1), Vec2(0, 1))) return false;

    if (n.x == 0.0f && n.y == 0.0f) return false; // started inside; normal collision handles it
    toi = tmin;
    normal = n; // points out of the rectangle, toward the circle
    return true;
}

#endif

#ifndef WORLD_H
#define WORLD_H

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "body.h"
#include "../Collision/collision.h"
#include "../Collision/collisionResponse.h"
#include "../Collision/sweep.h"

class World {
private:
    Vec2 gravity{0.0f, -9.8f};

    std::vector<Body> bodies{};

    const float fixedDt = 1.0f / 60.0f;
    float accumulator = 0.0f;

public:

    explicit World(Vec2 gravity) : gravity(gravity) {}

    void addBody(
        Vec2 position,
        float mass,
        std::unique_ptr<Shape> shape
    ) {
        bodies.emplace_back(
            position,
            mass,
            std::move(shape)
        );
    }

    void applyGravity() {
        for (Body& b : bodies) {
            Vec2 force = b.mass * gravity;
            b.applyForce(force);
        }
    }

    void physicsStep(float dt) {
        constexpr float maxSpeed = 40.0f;
        constexpr int velocityIterations = 8;
        constexpr int positionIterations = 3;

        // 1. Forces and integration (with speed clamp)
        applyGravity();

        for (Body& b : bodies) {
            b.updateVelocity(dt);

            float speed = b.velocity.mag();
            if (speed > maxSpeed) {
                b.velocity = b.velocity * (maxSpeed / speed);
            }

            b.updatePosition(dt);   // also stores prevPosition
            b.clearForces();
        }

        // 2. Swept test: dynamic circles vs static rectangles (stops tunneling)
        for (Body& c : bodies) {
            if (c.inverseMass == 0.0f || !c.shape ||
                c.shape->getType() != ShapeType::Circle) continue;

            const Circle& circle = static_cast<const Circle&>(*c.shape);

            for (Body& r : bodies) {
                if (r.inverseMass != 0.0f || !r.shape ||
                    r.shape->getType() != ShapeType::Rectangle) continue;

                const Rectangle& rect = static_cast<const Rectangle&>(*r.shape);

                Vec2 delta = c.position - c.prevPosition;
                float toi;
                Vec2 n;

                if (sweepCircleVsRect(c.prevPosition, delta, circle.radius,
                                    r, rect, toi, n)) {
                    c.position = c.prevPosition + delta * std::max(toi - 0.001f, 0.0f);

                    float vn = c.velocity.dot(n);
                    if (vn < 0.0f) {
                        float e = std::min(c.restitution, r.restitution);
                        c.velocity -= n * ((1.0f + e) * vn);
                    }
                }
            }
        }

        // 3. Find contacts once
        struct Contact { std::size_t a, b; collisionManifold m; };
        std::vector<Contact> contacts;

        for (std::size_t i = 0; i < bodies.size(); ++i) {
            for (std::size_t j = i + 1; j < bodies.size(); ++j) {
                Body& a = bodies[i];
                Body& b = bodies[j];

                if (a.inverseMass + b.inverseMass == 0.0f) continue; // static vs static

                collisionManifold m = checkCollision(a, b);
                if (m.colliding) contacts.push_back({i, j, m});
            }
        }

        // 4. Velocity pass (repeat so fixes propagate through piles)
        for (int it = 0; it < velocityIterations; ++it) {
            for (const Contact& c : contacts) {
                resolveCollision(bodies[c.a], bodies[c.b], c.m);
            }
        }

        // 5. Position pass (re-detect, since positions change)
        for (int it = 0; it < positionIterations; ++it) {
            for (const Contact& c : contacts) {
                collisionManifold m = checkCollision(bodies[c.a], bodies[c.b]);
                if (m.colliding) positionalCorrection(bodies[c.a], bodies[c.b], m);
            }
        }
    }

    void advance(float realElapsedTime) {
        accumulator += realElapsedTime;
        constexpr int substeps = 4;
        while (accumulator >= fixedDt) {
            for (int s = 0; s < substeps; ++s) physicsStep(fixedDt / substeps);
            accumulator -= fixedDt;
        }
    }

    float getInterpolationAlpha() const {
        return accumulator / fixedDt;
    }

    Body& getBody(std::size_t index) {

        if (index >= bodies.size()) {
            throw std::out_of_range(
                "Body index out of range"
            );
        }

        return bodies[index];
    }

    std::size_t getBodyCount() const {
        return bodies.size();
    }
};

#endif

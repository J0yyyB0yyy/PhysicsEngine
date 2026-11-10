
#ifndef WORLD_H
#define WORLD_H

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "body.h"
#include "Collision/collision.h"
#include "Collision/collisionResponse.h"

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
        applyGravity();

        for (Body& b : bodies) {
            b.update(dt);
        }

        for (std::size_t i = 0; i < bodies.size(); ++i) {

            for (std::size_t j = i + 1; j < bodies.size(); ++j) {

                Body& a = bodies[i];
                Body& b = bodies[j];

                const collisionManifold manifold =
                    checkCollision(a, b);

                if (!manifold.colliding) {
                    continue;
                }

                resolveCollision(a, b, manifold);
                positionalCorrection(a, b, manifold);
            }
        }
    }

    void advance(float realElapsedTime) {

        accumulator += realElapsedTime;

        while (accumulator >= fixedDt) {

            physicsStep(fixedDt);

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

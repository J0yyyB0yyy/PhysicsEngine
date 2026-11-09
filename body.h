#ifndef BODY_H
#define BODY_H

#include <memory>
#include <utility>
#include "vec2.h"
#include "shape.h"
class Body{
public:
    Vec2 position, prevPosition, velocity, force;

    float mass, inverseMass;
    float restitution = 0.0f;
    float friction = 0.5f;
    std::unique_ptr<Shape> shape;

    Body(Vec2 position, float mass, std::unique_ptr<Shape> shape)
        :position(position),
        prevPosition(position), 
        velocity(0, 0), force(0, 0), 
        mass(mass), 
        shape(std::move(shape)){

        if(mass<=0){
            inverseMass=0;
        }
        else{
            inverseMass=1/mass;
        }

    }

    void applyForce(const Vec2& f){
        this->force += f;
    }
    void clearForces()
    {
        force = Vec2(0, 0);
    }

    Vec2 calAccel()const{
        return Vec2(force.x*inverseMass, force.y*inverseMass);
    }

    void updateVelocity(float dt){
        Vec2 acc = calAccel();
        this->velocity+=dt*acc;
    }

    void updatePosition(float dt){
        this->prevPosition = position;
        this->position+=velocity*dt;
    }

    void update(float dt){
        updateVelocity(dt);
        updatePosition(dt);
        clearForces();
    }

    Vec2 getInterpolatedPosition(float alpha) const{
        Vec2 renderPosition = prevPosition+(position - prevPosition)*alpha;
        return renderPosition;
    }

};

#endif

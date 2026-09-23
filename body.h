#ifndef BODY_H
#define BODY_H

#include "vec2.h"

class Body{
public:
    Vec2 position, velocity, force;
    float mass, inverseMass; 

    Body(Vec2 position, float mass)
        :position(position), velocity(0, 0), force(0, 0), mass(mass){
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

    Vec2 calAccel(){
        return Vec2(force.x*inverseMass, force.y*inverseMass);
    }

    void updateVelocity(float t){
        Vec2 acc = calAccel();
        this->velocity+=t*acc;
    }

    void updatePosition(float t){
        this->position+=velocity*t;
    }

    void update(float t){
        updateVelocity(t);
        updatePosition(t);
        clearForces();
    }

};

#endif
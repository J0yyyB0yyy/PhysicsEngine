#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include<vector>
#include<stdexcept>
#include "body.h"



class World{
private:
    Vec2 gravity = Vec2(0, -9.8);
    std::vector<Body> bodies{};
    float fixedDt = 1.0f / 60.0f;
    float accumulator = 0.0f;
public:

    friend Vec2 interpolation(Vec2& prevPosition, Vec2& position);
    
    World(Vec2 gravity) :gravity(gravity){};

    void addBody(Vec2 position, float mass, std::unique_ptr<Shape> shape){
        bodies.emplace_back(position, mass, std::move(shape));
    }

    void applyGravity(){
        for(Body& b : bodies){
            Vec2 force=b.mass*gravity;
            b.applyForce(force);
        }
    }

    void physicsStep(float dt){
        applyGravity();
        for(Body& b : bodies){
            b.update(dt);
        }
    }

    void advance(float realElapsedTime){
        accumulator+=realElapsedTime;
        while(accumulator>=fixedDt){
            physicsStep(fixedDt);
            accumulator-=fixedDt;
        }
    }

    float getInterpolationAlpha() const{
        return (accumulator/fixedDt);
    };

    Body& getBody(int index) {
        if(index<0 || index>=bodies.size()){
            throw std::domain_error("Can't get body");
        }
        return bodies[index];
    }


};

#endif
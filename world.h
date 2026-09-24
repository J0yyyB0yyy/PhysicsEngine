#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include<vector>
#include "body.h"



class World{
private:
    Vec2 gravity = Vec2(0, -9.8);
    std::vector<Body> bodies{};
public:
    
    World(Vec2 gravity) :gravity(gravity){};

    void addBody(Vec2 position, float mass){
        bodies.push_back(Body(position, mass));
    }

    void applyGravity(){
        for(Body& b : bodies){
            Vec2 force=b.mass*gravity;
            b.applyForce(force);
        }
    }

    void update(float t){
        applyGravity();
        for(Body& b : bodies){
            b.update(t);
        }
    }

    Body& getBody(int index) {
        if(index<0 || index>=bodies.size()){
            throw std::domain_error("Can't get body");
        }
        return bodies[index];
    }


};

#endif
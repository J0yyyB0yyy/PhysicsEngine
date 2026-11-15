#pragma once

#include <stdexcept>

#include "../Physics/vec2.h"
#include "../Physics/body.h"
#include "../Physics/circle.h"
#include "../Physics/rectangle.h"

struct AABB{
    Vec2 min;
    Vec2 max;
};

bool overlaps(const AABB& a, const AABB& b){
    if(a.max.x<b.min.x){
        return false;
    }
    if(b.max.x<a.min.x){
        return false;
    }
    if(a.max.y < b.min.y){
        return false;
    }
    if(b.max.y<a.min.y){
        return false;
    }
    return true;

}

AABB getCircleAABB(const Vec2& position, float radius){
    AABB box;
    box.min = Vec2(position.x-radius, position.y-radius);
    box.max = Vec2(position.x+radius, position.y+radius);
    return box;
}

AABB getRectangleAABB(const Vec2& position, float width, float height){
    AABB box;
    box.min = Vec2(position.x-width/2.0f, position.y-height/2.0f);
    box.max = Vec2(position.x+width/2.0f, position.y+height/2.0f);
    return box;
}

AABB getAABB(const Body& body){

    if (!body.shape) {
        throw std::invalid_argument("Body has no shape");
    }
    ShapeType shape = body.shape->getType();

    if(shape == ShapeType::Circle){
        const Circle* circle = dynamic_cast<const Circle*>(body.shape.get());

        if (!circle) {
            throw std::runtime_error("Invalid circle shape");
        }

        return getCircleAABB(body.position, circle->radius);
    }

    if(shape == ShapeType::Rectangle){
        const Rectangle* rectangle = dynamic_cast<const Rectangle*>(body.shape.get());

        if (!rectangle) {
            throw std::runtime_error("Invalid rectangle shape");
        }

        return getRectangleAABB(body.position, rectangle->width, rectangle->height);
    }

    throw std::runtime_error("Unknown shape type");
}


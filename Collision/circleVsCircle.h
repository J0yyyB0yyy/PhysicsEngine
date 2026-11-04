
#include "body.h"
#include "circle.h"


bool circleVsCircle(const Body& a, const Body& b){

    Circle* circleA = dynamic_cast<Circle*>(a.shape.get());
    Circle* circleB = dynamic_cast<Circle*>(b.shape.get());

    if(circleA == nullptr || circleB == nullptr){
        return false;
    }

    Vec2 dist = (a.position - b.position);
    float radiSum = circleA->radius = circleB->radius;
    float radiSumSquared = radiSum*radiSum;

    return dist.magSquared() <= radiSumSquared;
   
}
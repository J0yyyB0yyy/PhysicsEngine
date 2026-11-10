#include<iostream>
#include "world.h"
#include "circle.h"
#include "rectangle.h"

using namespace std;

int main(){
    
    World w(Vec2(0, -9.8));
    w.addBody(Vec2(0, 100), 5.0, std::make_unique<Circle>(10));
    w.addBody(Vec2(89, 85), 2.0, std::make_unique<Rectangle>(10, 10));
    w.addBody(Vec2(112, 102), 3.0, std::make_unique<Circle>(10));

    for (int i = 0; i < 60; i++) {
        w.advance(1.0f / 60.0f);
    }
    for(int i=0; i<3; i++){
        Body& b=w.getBody(i);

        cout<<"Body "<<i <<" position is "<< b.position.x<<", "<<b.position.y<<endl;
        cout<<"Body "<<i<< " velocity is "<< b.velocity.x<<", "<<b.velocity.y<<endl;
    }

    

    return 0;
}
#include<iostream>
#include "world.h"

using namespace std;

int main(){
    
    World w(Vec2(0, -9.8));
    w.addBody(Vec2(0, 100), 5.0);
    Body& b=w.getBody(0);
    w.update(1);
    cout<<"Bodies position is "<< b.position.x<<", "<<b.position.y<<endl;
    cout<<"Bodies velocity is "<< b.velocity.x<<", "<<b.velocity.y<<endl;

    return 0;
}
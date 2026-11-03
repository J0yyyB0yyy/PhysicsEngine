#include<iostream>
#include "world.h"

using namespace std;

int main(){
    
    World w(Vec2(0, -9.8));
    w.addBody(Vec2(0, 100), 5.0);
    w.addBody(Vec2(89, 85), 2.0);
    w.addBody(Vec2(112, 102), 3.0);

    for(int i=0; i<3; i++){
        Body& b=w.getBody(i);
        cout<<"Body "<<i <<" position is "<< b.position.x<<", "<<b.position.y<<endl;
        cout<<"Body "<<i<< " velocity is "<< b.velocity.x<<", "<<b.velocity.y<<endl;
        
    }

    return 0;
}
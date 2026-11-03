#ifndef vec2_H
#define vec2_H

#include<cmath>
#include <stdexcept>

using namespace std;

class Vec2{
public:
    float x;
    float y;

    Vec2(float x, float y) : x(x), y(y) {}

    float mag() const{
        return std::sqrt((x*x + y*y));
    }

    float magSquared() const{
        return (x*x+y*y);
    }

    Vec2 unit() const{
        float len = mag();
        if(len<1e-6f){
            return Vec2(0.0f, 0.0f);
        }
        return Vec2(x/len, y/len);
    }

    Vec2 operator+(const Vec2& other) const{
        return Vec2(x+other.x, y+other.y);
    }

    Vec2& operator+=(const Vec2& other){
        this->x+=other.x;
        this->y+=other.y;
        return *this;
    }

    Vec2 operator-(const Vec2& other)const{
        return Vec2(x-other.x, y-other.y);
    }
    Vec2& operator-=(const Vec2& other){
        this->x-=other.x;
        this->y-=other.y;

        return *this;
    }

    Vec2 operator*(float n)const{
        return Vec2(n *x, n*y);
    }
    
    Vec2& operator*=(float n) {
        x *= n;
        y *= n;
        return *this;
    }
    friend Vec2 operator*(float scalar, const Vec2& v){
        return Vec2(v.x * scalar, v.y * scalar);
    }

    Vec2 operator/(float n)const{
        if(n==0.0f){
            throw std::domain_error("can't divide by zero\n");
        }
        return Vec2(x/n, y/n);
    }

    Vec2& operator/=(float n) {
        if (n == 0.0f) {
            throw std::domain_error("Cannot divide vector by zero");
        }

        x /= n;
        y /= n;

        return *this;
    }

    Vec2& operator=(const Vec2& other){
        x=other.x;
        y=other.y;
        return *this;
    }

    float dot(const Vec2& other)const{
        return (x*other.x + y*other.y);
    }

    float cross(const Vec2& other)const{
        return (x*other.y - y*other.x);
    }

};

#endif
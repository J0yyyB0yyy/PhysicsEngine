#include"../../include/Graphics/Renderer.h"
#include"../../include/Graphics/Renderer.h"
#include"../../include/Physics/circle.h"
#include"../../include/Physics/rectangle.h"
#include"../../include/Physics/shape.h"

#include <iostream>
#include <stdexcept>

struct CircleData{
    int x;
    int y;
    int radius;
};
struct RectangleData{
    int x;
    int y;
    int width;
    int height;
};

void drawFilledCircle( SDL_Renderer* renderer, int centerX, int centerY, int radius){
    for(int y =-radius;y<=radius;y++){
        int x = static_cast<int>(std::sqrt(radius*radius-y*y));
        SDL_RenderDrawLine(renderer, centerX-x, centerY+y, centerX+x, centerY+y);
    };
}

Renderer::Renderer(int width, int height) :window(nullptr), renderer(nullptr){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        throw std::runtime_error(SDL_GetError());
    }
    window = SDL_CreateWindow(
        "Physics Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );
    if(window==nullptr){
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr){
        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

}

Renderer::~Renderer(){
    if(renderer!=nullptr){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if(window!=nullptr){
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void Renderer:: clear(){
    SDL_RenderClear(renderer); 

}
void Renderer:: present(){
    SDL_RenderPresent(renderer);
}

void Renderer::drawBody(const Body& b){
    ShapeType s = b.shape->getType();
    if(s == ShapeType::Circle){
        const Circle* circle = dynamic_cast<const Circle*>(b.shape.get());
        if(circle == nullptr) return;
    }
    if(s ==ShapeType::Rectangle){
        const Rectangle* rectangle = dynamic_cast<const Rectangle*>(b.shape.get());
        if(rectangle == nullptr) return;
    }
}

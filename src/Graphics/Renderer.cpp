#include"../../include/Graphics/Renderer.h"
#include"../../include/Physics/circle.h"
#include"../../include/Physics/rectangle.h"
#include"../../include/Physics/shape.h"

#include <stdexcept>


void drawFilledCircle( SDL_Renderer* renderer, int centerX, int centerY, int radius){
    for(int y =-radius;y<=radius;y++){
        int x = static_cast<int>(std::sqrt(radius*radius-y*y));
        SDL_RenderDrawLine(renderer, centerX-x, centerY+y, centerX+x, centerY+y);
    };
}
Renderer::Renderer(int width, int height) :window(nullptr), renderer(nullptr), width(width), height(height){
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

void Renderer::setScale(float scale){
    if (scale <= 0.0f) {
        throw std::invalid_argument("Scale must be positive");
    }
    pixelsPerUnit=scale;
}
SDL_Point Renderer::worldToScreen(const Vec2 & position)const{
    SDL_Point point;
    point.x = static_cast<int>(width / 2.0f + position.x * pixelsPerUnit);
    point.y = static_cast<int>(height / 2.0f - position.y * pixelsPerUnit);
    return point;
}

Vec2 Renderer::screenToWorld(int sx, int sy) const {
    return Vec2((sx - width / 2.0f) / pixelsPerUnit, (height / 2.0f - sy) / pixelsPerUnit);
}

void Renderer::drawBody(const Body& b, float alpha){
    if (!b.shape) return;
    Vec2 renderPosition = b.getInterpolatedPosition(alpha);
    ShapeType s = b.shape->getType();
    if(s == ShapeType::Circle){

        const Circle* circle = dynamic_cast<const Circle*>(b.shape.get());
        if(circle == nullptr) return;
        
        SDL_Point center = worldToScreen(renderPosition);
        float radius = circle->radius;

        int screenRadius = static_cast<int>(radius*pixelsPerUnit);

        drawFilledCircle(renderer, center.x, center.y, screenRadius);  
    }
    else if(s ==ShapeType::Rectangle){
        const Rectangle* rectangle = dynamic_cast<const Rectangle*>(b.shape.get());
        if(rectangle == nullptr) return;

        float rectWidth = rectangle->width;
        float rectHeight = rectangle->height;

        float left = renderPosition.x - rectWidth / 2.0f;
        float top  = renderPosition.y + rectHeight / 2.0f;

        Vec2 topLeft(left, top);
        SDL_Point screenTopLeft = worldToScreen(topLeft);

        int screenWidth = static_cast<int>(rectWidth * pixelsPerUnit);
        int screenHeight = static_cast<int>(rectHeight * pixelsPerUnit);


        SDL_Rect r = {screenTopLeft.x, screenTopLeft.y, screenWidth, screenHeight};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &r);
    }


}


#pragma once

#include <SDL2/SDL.h>
#include "../Physics/body.h"

class Renderer{
public:
    Renderer(int width, int height);
    ~Renderer();
    
    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void clear();
    void drawBody(const Body& body);
    void present();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

};
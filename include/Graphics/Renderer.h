#pragma once

#include <SDL2/SDL.h>
#include "../Physics/body.h"

class Renderer{
public:
    Renderer(int width, int height);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void clear();
    void drawBody(const Body& body, float alpha);
    void present();
    void setScale(float scale);

    SDL_Point worldToScreen(const Vec2& position) const;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    float pixelsPerUnit = 50.0f;
};
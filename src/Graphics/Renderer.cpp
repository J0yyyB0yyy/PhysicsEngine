#include"../../include/Graphics/Renderer.h"
#include <iostream>
#include <stdexcept>

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
    

}

#include<iostream>
#include<SDL2/SDL.h>

int main(){

    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cerr << "SDL initalization failed: "<<SDL_GetError()<<'\n';
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Physics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if(window==nullptr){
        std::cerr << "Window creation failed: "<<SDL_GetError()<<"\n";
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        std::cerr << "renderer createion failed: "<<SDL_GetError()<<'\n';

        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    bool running = true;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 20, 20 , 30 , 255);
        SDL_RenderClear(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
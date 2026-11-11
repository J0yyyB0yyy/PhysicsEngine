#include<iostream>
#include <cmath>
#include<vector>
#include<SDL2/SDL.h>

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

std::vector<CircleData> circles;
std::vector<RectangleData> rectangles;

void drawFilledCircle( SDL_Renderer* renderer, int centerX, int centerY, int radius){
    for(int y =-radius;y<=radius;y++){
        int x = static_cast<int>(std::sqrt(radius*radius-y*y));
        SDL_RenderDrawLine(renderer, centerX-x, centerY+y, centerX+x, centerY+y);
    };
}

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
            if(event.type == SDL_KEYDOWN){
                const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
                if(event.key.keysym.sym==SDLK_ESCAPE){
                    running = false;
                }

            }
            if(event.type==SDL_MOUSEBUTTONDOWN){
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                std::cout << "Clicked at: "<< mouseX << ", " << mouseY << '\n';

                if(event.button.button == SDL_BUTTON_LEFT){
                    circles.push_back({mouseX, mouseY, 30});
                }
                if(event.button.button == SDL_BUTTON_RIGHT){
                    rectangles.push_back({mouseX-20, mouseY-30, 40, 60});
                };

                SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                for(const CircleData& circle : circles){
                    drawFilledCircle(renderer, circle.x, circle.y, circle.radius);
                }
                SDL_SetRenderDrawColor(renderer, 255, 123, 145, 255);
                for(const RectangleData& rectangle : rectangles){
                    SDL_Rect rect = {rectangle.x-15, rectangle.y-20, rectangle.width, rectangle.height};
                    SDL_RenderFillRect(renderer, &rect);
                }
                SDL_RenderPresent(renderer);
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
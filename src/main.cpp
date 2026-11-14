#include <iostream>
#include <memory>
#include <algorithm>
#include <random>

#include "../include/Physics/world.h"
#include "../include/Physics/circle.h"
#include "../include/Physics/rectangle.h"
#include "../include/Graphics/Renderer.h"

int main() {

    World world(Vec2(0.0f, -9.8f));

    Renderer renderer(1280, 720);

    renderer.setScale(50.0f);

    for(int i=0; i<100;i++){
        world.addBody(Vec2(-5.0f, 2.0f),0.01f,std::make_unique<Circle>(0.15f));
        world.getBody(world.getBodyCount() - 1).restitution = 0.8f;
        world.getBody(world.getBodyCount() - 1).velocity = Vec2(300.0f,0.0f);
        world.getBody(world.getBodyCount() - 1).friction = 0.0f;

    }

    world.addBody(Vec2(0.0f, 6.5f),0.0f,std::make_unique<Rectangle>(25.0f, 1.0f));
    world.getBody(world.getBodyCount() - 1).restitution = 1.0f;
    world.getBody(world.getBodyCount() - 1).friction = 0.0f;

    world.addBody(Vec2(-12.0f, 0.0),0.0f,std::make_unique<Rectangle>(1.0f, 13.0f));
    world.getBody(world.getBodyCount() - 1).restitution = 1.0f;
    world.getBody(world.getBodyCount() - 1).friction = 0.0f;

    
    world.addBody(Vec2(0.0f, -6.5f),0.0f,std::make_unique<Rectangle>(25.0f, 1.0f));
    world.getBody(world.getBodyCount() - 1).restitution = 1.0f;
    world.getBody(world.getBodyCount() - 1).friction = 0.0f;

    world.addBody(Vec2(12.0f, 0.0f),0.0f,std::make_unique<Rectangle>(1.0f, 13.0f));
    world.getBody(world.getBodyCount() - 1).restitution = 1.0f;
    world.getBody(world.getBodyCount() - 1).friction = 0.0f;

    Uint64 previousTime = SDL_GetPerformanceCounter();

    bool running = true;
    SDL_Event event;
    
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx, my;
                Uint32 buttons = SDL_GetMouseState(&mx, &my);
                if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    Vec2 p = renderer.screenToWorld(mx, my);
                    world.addBody(p, 1.0f, std::make_unique<Circle>(0.15f));
                    world.getBody(world.getBodyCount() - 1).restitution = 1.0f;
                }
            }
        }

        Uint64 currentTime = SDL_GetPerformanceCounter();

        float deltaTime = static_cast<float>(
            currentTime - previousTime
        ) / SDL_GetPerformanceFrequency();

        deltaTime = std::min(deltaTime, 0.05f);

        previousTime = currentTime;

        world.advance(deltaTime);

        // 4. Render
        renderer.setDrawColor(20, 20, 30, 255);
        renderer.clear();

        renderer.setDrawColor(255, 255, 255, 255);
        float alpha = world.getInterpolationAlpha();
        for (std::size_t i = 0; i < world.getBodyCount(); ++i) {
            renderer.drawBody(world.getBody(i), alpha);
        }

        renderer.present();
    }
    return 0;

}
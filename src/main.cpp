#include <iostream>
#include <memory>
#include <algorithm>

#include "../include/Physics/world.h"
#include "../include/Physics/circle.h"
#include "../include/Physics/rectangle.h"
#include "../include/Graphics/Renderer.h"

int main() {

    World world(Vec2(0.0f, -9.8f));

    Renderer renderer(1280, 720);

    renderer.setScale(50.0f);

    world.addBody(
        Vec2(0.0f, 5.0f),
        1.0f,
        std::make_unique<Circle>(1.0f)
    );

    world.addBody(
        Vec2(3.0f, 5.0f),
        1.0f,
        std::make_unique<Rectangle>(2.0f, 2.0f)
    );
    world.addBody(
        Vec2(0.0f, -6.5f),
        0.0f,
        std::make_unique<Rectangle>(25.0f, 1.0f)
    );

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
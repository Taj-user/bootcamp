#include <iostream>
#include <SDL2/SDL.h>
#include "World.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
        if(SDL_Init(SDL_INIT_VIDEO) != 0) {
                std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
                return 1;
        }

        SDL_Window* window = SDL_CreateWindow(
                        "engine",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        800, 600,
                        SDL_WINDOW_SHOWN
                        );

        if(!window) {
                std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
                SDL_Quit();
                return 1;
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == nullptr) {
                std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 1;
        }

        World world;
        Entity square = world.create_entity();
        PhysicsSystem physics;

        Position p_square(600, 400);
        Velocity v_square(0, -1);

        world.add_position(square, p_square);
        world.add_velocity(square, v_square);

        bool running = true;
        double accumulator {0.0};
        Uint32 previous_time = SDL_GetTicks();
        double FIXED_TIMESTAMP = 16.6666;
        SDL_Rect rectangle = { 0, 0, 200, 200 };

        while(running) {
                Uint32 current_time = SDL_GetTicks();
                Uint32 delta_time = current_time - previous_time;
                previous_time = current_time;
                accumulator += delta_time;
                SDL_Event event;
                while(SDL_PollEvent(&event)) {
                        if(event.type == SDL_QUIT) running = false;
                }
                while(accumulator >= FIXED_TIMESTAMP) {
                        physics.update(world);
                        accumulator -= FIXED_TIMESTAMP;
                }
                rectangle.x = world.get_positions().at(square).x;
                rectangle.y = world.get_positions().at(square).y;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 128, 20, 128, 255);
                SDL_RenderFillRect(renderer, &rectangle);
                SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
}

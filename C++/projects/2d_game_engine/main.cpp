#include <iostream>
#include "Collision.hpp"
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
        Entity wall = world.create_entity();
        PhysicsSystem physics;

        Position p_square(400, 300);
        Velocity v_square(0, 0);

        Position p_wall(100, 100);

        world.add_position(square, p_square);
        world.add_velocity(square, v_square);

        world.add_position(wall, p_wall);

        bool running = true;
        double accumulator {0.0};
        Uint32 previous_time = SDL_GetTicks();
        double FIXED_TIMESTAMP = 16.6666;
        SDL_Rect rectangle = { 0, 0, 200, 200 };
        SDL_Rect rectangle2 = { 0, 0, 200, 300 };

        while(running) {
                Uint32 current_time = SDL_GetTicks();
                Uint32 delta_time = current_time - previous_time;
                previous_time = current_time;
                accumulator += delta_time;
                SDL_Event event;

                while(SDL_PollEvent(&event)) {
                        if(event.type == SDL_QUIT) running = false;
                        if(event.type == SDL_KEYDOWN) {
                                switch(event.key.keysym.sym) {
                                        case SDLK_ESCAPE:
                                                running = false;
                                                break;
                                }
                        }
                }

                world.get_velocities().at(square).dx = 0;
                world.get_velocities().at(square).dy = 0;

                const Uint8* keys = SDL_GetKeyboardState(nullptr);
                if(keys[SDL_SCANCODE_UP]) {                                                             // up arrow key
                        world.get_velocities().at(square).dy = -2;
                }
                if(keys[SDL_SCANCODE_DOWN]) {                                                           // down arrow key
                        world.get_velocities().at(square).dy = 2;
                }
                if(keys[SDL_SCANCODE_LEFT]) {                                                           // left arrow key
                        world.get_velocities().at(square).dx = -2;
                }
                if(keys[SDL_SCANCODE_RIGHT]) {                                                          // right arrow key
                        world.get_velocities().at(square).dx = 2;
                }

                float square_old_x = world.get_positions().at(square).x;
                float square_old_y = world.get_positions().at(square).y;

                while(accumulator >= FIXED_TIMESTAMP) {
                        physics.update(world);
                        accumulator -= FIXED_TIMESTAMP;
                }

                rectangle.x = world.get_positions().at(square).x;
                rectangle.y = world.get_positions().at(square).y;
                if(is_colliding(rectangle, rectangle2)) {
                        world.get_positions().at(square).x = square_old_x;
                        world.get_positions().at(square).y = square_old_y;
                        rectangle.x = square_old_x;
                        rectangle.y = square_old_y;
                }
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 0, 150, 150, 255);
                SDL_RenderFillRect(renderer, &rectangle2);

                SDL_SetRenderDrawColor(renderer, 128, 20, 128, 255);
                SDL_RenderFillRect(renderer, &rectangle);

                SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
}

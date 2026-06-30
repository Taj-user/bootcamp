#include <SDL2/SDL.h>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
        if(SDL_Init(SDL_INIT_VIDEO) != 0) {
                std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
                return 1;
        }

        SDL_Window* window = SDL_CreateWindow(
                        "SDL2 Test",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        800, 600,
                        SDL_WINDOW_SHOWN
                        );

        if(!window) {
                std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
                SDL_Quit();
                return 1;
        }

        SDL_Delay(3000);

        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
}

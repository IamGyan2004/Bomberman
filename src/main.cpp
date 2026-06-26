#include "game.h"
#include "renderer.h"
#include <iostream>
#include <thread>
#include <chrono>
#ifdef USE_SDL2
#include <SDL2/SDL.h>
#endif

int main(int argc, char* argv[]) {
    Game game;
    std::string levelPath = "levels/level1.txt";
    if (argc > 1) {
        levelPath = argv[1];
    }

    if (!game.loadLevel(levelPath)) {
        return 1;
    }

    Renderer renderer(game.getWidth(), game.getHeight());
    if (!renderer.initialize()) {
        return 1;
    }

    while (game.isRunning()) {
        game.update();
        game.render(renderer);
#ifdef USE_SDL2
        if (!renderer.isTerminalMode()) {
            SDL_Delay(200);
            continue;
        }
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}

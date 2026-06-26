#include "renderer.h"
#include <iostream>
#include <cstdlib>

#ifdef USE_SDL2
#include <SDL2/SDL.h>
#endif

Renderer::Renderer(int width, int height)
    : width(width), height(height), terminalMode(false)
#ifdef USE_SDL2
    , window(nullptr), renderer(nullptr)
#endif
{
}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize() {
#ifdef USE_SDL2
    bool hasDisplay = std::getenv("DISPLAY") != nullptr || std::getenv("WAYLAND_DISPLAY") != nullptr;
    bool hasRuntime = std::getenv("XDG_RUNTIME_DIR") != nullptr;
    if (!hasDisplay || !hasRuntime) {
        std::cerr << "Headless environment detected, using terminal rendering.\n";
        terminalMode = true;
        return true;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        std::cerr << "Falling back to terminal rendering.\n";
        terminalMode = true;
        return true;
    }
    window = SDL_CreateWindow("Bomberman",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width * 32,
                              height * 32,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        std::cerr << "Falling back to terminal rendering.\n";
        terminalMode = true;
        SDL_Quit();
        return true;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        std::cerr << "Trying software renderer.\n";
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if (!renderer) {
            std::cerr << "SDL_CreateRenderer software Error: " << SDL_GetError() << "\n";
            std::cerr << "Falling back to terminal rendering.\n";
            terminalMode = true;
            SDL_DestroyWindow(window);
            window = nullptr;
            SDL_Quit();
            return true;
        }
    }
    return true;
#else
    terminalMode = true;
    return true;
#endif
}

void Renderer::render(const std::vector<std::string>& levelData) {
    if (terminalMode) {
        std::cout << "\x1B[2J\x1B[H";
        for (const auto& line : levelData) {
            std::cout << line << "\n";
        }
        std::cout << std::flush;
        return;
    }

#ifdef USE_SDL2
    if (!renderer) return;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < (int)levelData.size(); ++y) {
        for (int x = 0; x < (int)levelData[y].size(); ++x) {
            char c = levelData[y][x];
            SDL_Rect rect{ x * 32, y * 32, 32, 32 };
            switch (c) {
                case '#': SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); break;
                case 'B': SDL_SetRenderDrawColor(renderer, 160, 82, 45, 255); break;
                case 'P': SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break;
                case 'E': SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
                case 'o': SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break;
                case 'x': SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break;
                default: SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); break;
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
#endif
}

void Renderer::cleanup() {
#ifdef USE_SDL2
    if (!terminalMode) {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        SDL_Quit();
    }
#endif
}

bool Renderer::isTerminalMode() const {
    return terminalMode;
}

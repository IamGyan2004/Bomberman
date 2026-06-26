#pragma once

#include <vector>
#include <string>

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();
    bool initialize();
    void render(const std::vector<std::string>& levelData);
    void cleanup();
    bool isTerminalMode() const;

private:
    int width;
    int height;
    bool terminalMode;
#ifdef USE_SDL2
    struct SDL_Window* window;
    struct SDL_Renderer* renderer;
#endif
};

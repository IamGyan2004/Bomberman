#pragma once

#include <vector>
#include <string>

struct Position {
    int x;
    int y;
};

enum class Tile {
    Empty,
    Wall,
    Block,
    Player,
    Enemy,
    Bomb,
    Explosion,
};

class Renderer;

class Game {
public:
    Game();
    bool loadLevel(const std::string& path);
    void update();
    void render(Renderer& renderer);
    bool isRunning() const;
    int getWidth() const;
    int getHeight() const;

private:
    void updatePlayer();
    void updateEnemies();
    void updateBombs();
    void applyExplosions();
    void advanceLevel();
    bool canMove(int x, int y) const;

    std::vector<std::string> levelData;
    int width;
    int height;
    Position player;
    std::vector<Position> enemies;
    std::vector<Position> bombs;
    std::vector<Position> explosions;
    int levelIndex;
    bool running;
};

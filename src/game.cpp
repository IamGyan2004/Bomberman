#include "game.h"
#include "level.h"
#include "renderer.h"
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

Game::Game()
    : width(0), height(0), levelIndex(1), running(true) {
    std::srand((unsigned)std::time(nullptr));
}

bool Game::loadLevel(const std::string& path) {
    if (!loadLevelFile(path, levelData)) {
        return false;
    }

    height = static_cast<int>(levelData.size());
    width = height > 0 ? static_cast<int>(levelData[0].size()) : 0;
    enemies.clear();
    bombs.clear();
    explosions.clear();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char c = levelData[y][x];
            if (c == 'P') {
                player = {x, y};
            } else if (c == 'E') {
                enemies.push_back({x, y});
            }
        }
    }
    return true;
}

void Game::update() {
    updatePlayer();
    updateEnemies();
    updateBombs();
    applyExplosions();
}

void Game::render(Renderer& renderer) {
    renderer.render(levelData);
}

bool Game::isRunning() const {
    return running;
}

int Game::getWidth() const {
    return width;
}

int Game::getHeight() const {
    return height;
}

void Game::updatePlayer() {
    // Placeholder: simple no-input player logic for a demo.
}

void Game::updateEnemies() {
    for (auto& enemy : enemies) {
        int dx = player.x - enemy.x;
        int dy = player.y - enemy.y;
        int stepX = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
        int stepY = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
        if (std::abs(dx) > std::abs(dy)) {
            if (canMove(enemy.x + stepX, enemy.y)) {
                enemy.x += stepX;
            } else if (canMove(enemy.x, enemy.y + stepY)) {
                enemy.y += stepY;
            }
        } else {
            if (canMove(enemy.x, enemy.y + stepY)) {
                enemy.y += stepY;
            } else if (canMove(enemy.x + stepX, enemy.y)) {
                enemy.x += stepX;
            }
        }
        if (enemy.x == player.x && enemy.y == player.y) {
            running = false;
            std::cout << "Player was caught by an enemy!\n";
        }
    }
}

void Game::updateBombs() {
    // Placeholder: bombs not implemented yet.
}

void Game::applyExplosions() {
    // Placeholder: explosion logic not implemented.
}

void Game::advanceLevel() {
    ++levelIndex;
    std::string nextPath = "levels/level" + std::to_string(levelIndex) + ".txt";
    if (!loadLevel(nextPath)) {
        running = false;
        std::cout << "No more levels available.\n";
    }
}

bool Game::canMove(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return false;
    }
    char tile = levelData[y][x];
    return tile == '.' || tile == 'P' || tile == 'E';
}

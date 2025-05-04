#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <FL/Fl.H>
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"

class GameModel {
private:
    const int MIN_ASTEROIDS = 5;

    int width;
    int height;
    int score;
    bool gameOver;

    std::unique_ptr<Ship> ship;
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<Bullet>> bullets;

    void spawnAsteroids(int count);
    void spawnAsteroid();
    void splitAsteroid(Asteroid& parent, std::vector<std::unique_ptr<Asteroid>>& newAsteroids);

public:
    GameModel(int w, int h);

    void update();
    void handleInput(int key, bool pressed);
    void fireBullet();
    void removeOutOfBoundsObjects();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getScore() const { return score; }
    bool isGameOver() const { return gameOver; }
    Ship* getShip() const { return ship.get(); }
    const std::vector<std::unique_ptr<Asteroid>>& getAsteroids() const { return asteroids; }
    const std::vector<std::unique_ptr<Bullet>>& getBullets() const { return bullets; }

    void resetGame();
    bool isGameOver();

    void handleShipCollision();
};
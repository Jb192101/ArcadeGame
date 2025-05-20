#pragma once
#include <vector>
#include <memory>
#include <future>
#include <atomic>
#include <chrono>
#include <thread>
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"

class GameModel 
{
private:
    const int MIN_ASTEROIDS = 5;
    const int MIN_BULLETS = 5;
    const int MAX_BULLETS = 4;
    const int COOLDOWN_FRAMES = 10;

    int m_bulletCooldown = 0;

    int m_width;
    int m_height;
    int m_score;
    std::atomic<bool> m_gameOver{ false };

    std::unique_ptr<Ship> m_ship;
    std::vector<std::unique_ptr<Asteroid>> m_asteroids;
    std::vector<std::unique_ptr<Bullet>> m_bullets;

    void spawnAsteroids(int count);
    void spawnAsteroid();
    void splitAsteroid(Asteroid& parent, std::vector<std::unique_ptr<Asteroid>>& newAsteroids);
    void splitAsteroid(Asteroid& asteroid);

    std::thread m_updateThread;

public:
    GameModel(int w, int h);
    ~GameModel();

    void start();
    void stop();
    void update();

    void fireBullet();
    void removeOutOfBoundsObjects();

    int getWidth() const;
    int getHeight() const;
    int getScore() const;
    bool getGameOver() const;
    Ship* getShip() const;
    const std::vector<std::unique_ptr<Asteroid>>& getAsteroids() const;
    const std::vector<std::unique_ptr<Bullet>>& getBullets() const;

    void resetGame();

    void handleShipCollision();
    void cleanUpBullets();
};
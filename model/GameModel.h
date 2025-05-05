#pragma once
#include <vector>
#include <future>
#include <memory>
#include <algorithm>
#include <FL/Fl.H>
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"

class GameModel {
private:
    const int MIN_ASTEROIDS = 5;
    const int MIN_BULLETS = 5;
    const int MAX_BULLETS = 4; // Максимальное количество пуль
    const int COOLDOWN_FRAMES = 10;

    int m_bulletCooldown = 0;          // Таймер перезарядки/

    int m_width;
    int m_height;
    int m_score;
    bool m_gameOver;

    struct CollisionTaskResult {
        std::vector<size_t> bulletsToRemove;
        std::vector<size_t> asteroidsToRemove;
        std::vector<std::unique_ptr<Asteroid>> newAsteroids;
        int scoreToAdd = 0;
        bool shipCollision = false;
    };

    std::unique_ptr<Ship> m_ship;
    std::vector<std::unique_ptr<Asteroid>> m_asteroids;
    std::vector<std::unique_ptr<Bullet>> m_bullets;

    void spawnAsteroids(int count);
    void spawnAsteroid();
    void splitAsteroid(Asteroid& parent, std::vector<std::unique_ptr<Asteroid>>& newAsteroids);
    void splitAsteroid(Asteroid& asteroid);

    std::mutex m_collisionMutex;
    std::vector<std::future<CollisionTaskResult>> m_collisionFutures;

    void asyncCheckCollisions();
    void asyncUpdatePositions();
    void processCollisionResults();

public:
    GameModel(int w, int h);

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
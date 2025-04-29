#pragma once
#include <memory>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include "SpaceShipModel.h"
#include "AsteroidModel.h"
#include "BulletModel.h"

#include "Vector2D.h"
#include "Size.c"

# define M_PI           3.14159265358979323846

class GameModel
{
private:
    std::unique_ptr<SpaceShipModel> ship;
    std::vector<std::unique_ptr<AsteroidModel>> asteroids;
    std::vector<std::unique_ptr<BulletModel>> bullets;

    int score;
    bool gameOver;
    float asteroidSpawnTimer;
    float invincibilityDuration;

    int w, h; // Размеры игрового окна

    Vector2D randomOffscreenPosition();
    Vector2D randomVelocity(float minSpeed, float maxSpeed);

    bool checkCollision(Model& obj1, Model& obj2, float radius1, float radius2);

    void spawnAsteroid();
    void splitAsteroid(size_t index);
public:
    GameModel();
    void update(float deltaTime);

    // Управление кораблем
    void rotateShip(float angle);
    void setShipThrusting(bool isThrusting);
    void shipShoot();

    const SpaceShipModel& getShip() const { return *ship; }
    const std::vector<std::unique_ptr<AsteroidModel>>& getAsteroids() const { return asteroids; }
    const std::vector<std::unique_ptr<BulletModel>>& getBullets() const { return bullets; }
    int getScore() const { return score; }
    bool isGameOver() const { return gameOver; }
};

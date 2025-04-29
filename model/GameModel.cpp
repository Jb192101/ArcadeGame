#include "GameModel.h"

Vector2D GameModel::randomOffscreenPosition() {
    int side = rand() % 4;
    float x, y;

    switch (side) {
    case 0: // верх
        x = static_cast<float>(rand()) / RAND_MAX;
        y = 1.1f;
        break;
    case 1: // право
        x = 1.1f;
        y = static_cast<float>(rand()) / RAND_MAX;
        break;
    case 2: // низ
        x = static_cast<float>(rand()) / RAND_MAX;
        y = -0.1f;
        break;
    case 3: // лево
        x = -0.1f;
        y = static_cast<float>(rand()) / RAND_MAX;
        break;
    }

    return Vector2D(x, y);
}

Vector2D GameModel::randomVelocity(float minSpeed, float maxSpeed) {
    float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
    float speed = minSpeed + static_cast<float>(rand()) / RAND_MAX * (maxSpeed - minSpeed);
    return Vector2D(std::cos(angle), std::sin(angle)) * speed;
}

bool GameModel::checkCollision(Model& obj1, Model& obj2, float radius1, float radius2) {
    float dx = obj1.getPosition().getX() - obj2.getPosition().getX();
    float dy = obj1.getPosition().getX() - obj2.getPosition().getX();;

    // Учитываем зацикливание пространства
    //if (dx > 0.5f) dx -= 1.0f;
    //if (dx < -0.5f) dx += 1.0f;
    //if (dy > 0.5f) dy -= 1.0f;
    //if (dy < -0.5f) dy += 1.0f;

    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = radius1 + radius2;
    return distanceSquared < radiusSum * radiusSum;
}

void GameModel::spawnAsteroid() {
    Vector2D pos = randomOffscreenPosition();
    Vector2D vel = randomVelocity(0.05f, 0.15f);
    asteroids.push_back(std::make_unique<AsteroidModel>(pos, vel, 1.0f));
}

void GameModel::splitAsteroid(size_t index) {
    auto& asteroid = asteroids[index];

    if (asteroid->getSize() == MEDIUM || asteroid->getSize() == LARGE) {
        Size newSize = Size(SMALL);
        Vector2D vel1 = asteroid->getVelocity().rotated(M_PI / 4) * 1.5f;
        Vector2D vel2 = asteroid->getVelocity().rotated(-M_PI / 4) * 1.5f;

        asteroids.push_back(std::make_unique<AsteroidModel>(asteroid->getPosition(), vel1, newSize));
        asteroids.push_back(std::make_unique<AsteroidModel>(asteroid->getPosition(), vel2, newSize));
    }

    asteroids.erase(asteroids.begin() + index);
}

GameModel::GameModel()
    : ship(std::make_unique<SpaceShipModel>()),
    score(0), gameOver(false),
    asteroidSpawnTimer(0), invincibilityDuration(3.0f)
{
    // Начальные астероиды
    for (int i = 0; i < 4; ++i) {
        spawnAsteroid();
    }

    // Начальная неуязвимость корабля
    ship->setInvincibilityTime(invincibilityDuration);
}

void GameModel::update(float deltaTime) {
    if (gameOver) return;

    // Обновление корабля
    ship->Update(deltaTime, w, h);

    // Обновление пуль
    for (auto& bullet : bullets) {
        bullet->Update(deltaTime, w, h);
    }

    // Удаление "мертвых" пуль
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const std::unique_ptr<BulletModel>& b) { return !b->isAlive(); }),
        bullets.end()
    );

    // Обновление астероидов
    for (auto& asteroid : asteroids) {
        asteroid->Update(deltaTime, w, h);
    }

    // Спавн новых астероидов
    asteroidSpawnTimer += deltaTime;
    if (asteroidSpawnTimer > 10.0f && asteroids.size() < 10) {
        spawnAsteroid();
        asteroidSpawnTimer = 0;
    }

    // Проверка столкновений пуль с астероидами
    for (size_t i = 0; i < bullets.size(); ) {
        bool bulletHit = false;

        float sizeFloat;
        for (size_t j = 0; j < asteroids.size(); ) {
            sizeFloat = asteroids[j]->sizeAtFloat();

            if (checkCollision(*bullets[i], *asteroids[j], 0.005f, 0.05f * sizeFloat)) {
                // Уничтожение астероида
                score += static_cast<int>(100 / sizeFloat);
                splitAsteroid(j);
                bulletHit = true;
                break;
            }
            else {
                ++j;
            }
        }

        if (bulletHit) {
            bullets.erase(bullets.begin() + i);
        }
        else {
            ++i;
        }
    }

    // Проверка столкновений корабля с астероидами
    if (!ship->isInvincible()) {
        for (size_t i = 0; i < asteroids.size(); ) {
            if (checkCollision(*ship, *asteroids[i], 0.02f, 0.05f * asteroids[i]->getSize())) {
                gameOver = true;
                break;
            }
            else {
                ++i;
            }
        }
    }
}

// Управление кораблем
void GameModel::rotateShip(float angle) {
    ship->rotate(angle);
}

void GameModel::setShipThrusting(bool isThrusting) {
    ship->setThrusting(isThrusting);
}

void GameModel::shipShoot() {
    if (bullets.size() < 10) {
        bullets.push_back(std::make_unique<BulletModel>(ship->shoot()));
    }
}
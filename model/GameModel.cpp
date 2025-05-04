#include "GameModel.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

GameModel::GameModel(int w, int h) : width(w), height(h), score(0), gameOver(false) {
    std::srand(std::time(nullptr));
    resetGame();

    ship->setWrapEnabled(true);
}

void GameModel::removeOutOfBoundsObjects() {
    // Удаляем астероиды
    auto asteroidIt = asteroids.begin();
    while (asteroidIt != asteroids.end()) {
        if ((*asteroidIt)->isOutOfBounds(width, height)) {
            asteroidIt = asteroids.erase(asteroidIt);
        }
        else {
            ++asteroidIt;
        }
    }

    // Удаляем пули
    auto bulletIt = bullets.begin();
    while (bulletIt != bullets.end()) {
        if ((*bulletIt)->isOutOfBounds(width, height)) {
            bulletIt = bullets.erase(bulletIt);
        }
        else {
            ++bulletIt;
        }
    }
}

void GameModel::resetGame() {
    ship = std::make_unique<Ship>(Vector2D(width / 2, height / 2), Vector2D(0, 0), 0, 20.0);
    asteroids.clear();
    bullets.clear();
    score = 0;
    gameOver = false;
    spawnAsteroids(4);
}

void GameModel::spawnAsteroids(int count) {
    for (int i = 0; i < count; i++) {
        double x = rand() % width;
        double y = rand() % height;
        double vx = (rand() % 100) / 100.0 * 2 - 1;
        double vy = (rand() % 100) / 100.0 * 2 - 1;
        double angle = rand() % 360;

        // Make sure asteroid doesn't spawn on top of ship
        while (Vector2D(x, y).magnitude() < 100) {
            x = rand() % width;
            y = rand() % height;
        }

        asteroids.push_back(std::make_unique<Asteroid>(Vector2D(x, y), Vector2D(vx, vy), angle));
    }
}

void GameModel::splitAsteroid(Asteroid& parent, std::vector<std::unique_ptr<Asteroid>>& newAsteroids) {
    int fragments = 2 + (rand() % 2);  // 2 или 3 фрагмента
    for (int i = 0; i < fragments; i++) {
        double angle = rand() % 360;
        double speed = 1.0 + (rand() % 100) / 100.0;  // Скорость от 1.0 до 2.0

        Vector2D vel(
            cos(angle * M_PI / 180.0) * speed,
            sin(angle * M_PI / 180.0) * speed
        );

        newAsteroids.push_back(std::make_unique<Asteroid>(
            parent.getPosition(),
            vel,
            angle,
            parent.getSize() / (1.3 + (rand() % 40) / 100.0),  // Размер от 1.3 до 1.7 меньше
            parent.getGeneration() - 1
        ));
    }
}

void GameModel::spawnAsteroid() {
    // Генерация случайных параметров
    double x = rand() % width;
    double y = rand() % height;

    // Убедимся, что астероид не появляется слишком близко к кораблю
    while (Vector2D(x - ship->getPosition().getX(), y - ship->getPosition().getY()).magnitude() < 150) {
        x = rand() % width;
        y = rand() % height;
    }

    double vx = (rand() % 100) / 100.0 * 2 - 1;  // Скорость от -1 до 1
    double vy = (rand() % 100) / 100.0 * 2 - 1;
    double angle = rand() % 360;
    int generation = 3;  // Максимальный размер

    double size = 20.0 + (rand() % 20);  // От 20 до 40px

    // Иногда создаем более мелкие астероиды
    if (rand() % 4 == 0) {  // 25% chance
        size /= 1.5;
        generation = 2;
    }

    asteroids.push_back(std::make_unique<Asteroid>(
        Vector2D(x, y),
        Vector2D(vx, vy),
        angle,
        30.0,  // Размер
        generation
    ));
}

void GameModel::update() {
    // 1. Обновляем состояния всех объектов
    removeOutOfBoundsObjects();

    for (auto& asteroid : asteroids) {
        asteroid->update();
        if (asteroid->getWrapEnabled()) asteroid->wrapAround(width, height);
    }

    for (auto& bullet : bullets) {
        bullet->update();
        if (bullet->getWrapEnabled()) bullet->wrapAround(width, height);
    }

    ship->update();
    if (ship->getWrapEnabled()) ship->wrapAround(width, height);

    // 3. Обновляем оставшиеся объекты
    for (auto& asteroid : asteroids) asteroid->update();
    for (auto& bullet : bullets) bullet->update();
    ship->update();

    // 2. Обработка столкновений пуль с астероидами
    std::vector<std::unique_ptr<Asteroid>> newAsteroids;
    std::vector<size_t> bulletsToRemove;
    std::vector<size_t> asteroidsToRemove;

    for (size_t b = 0; b < bullets.size(); ++b) {
        if (!bullets[b]->isActive()) continue;

        for (size_t a = 0; a < asteroids.size(); ++a) {
            if (!asteroids[a]->isActive()) continue;

            if (bullets[b]->checkCollision(*asteroids[a])) {
                // Запоминаем индексы объектов для удаления
                bulletsToRemove.push_back(b);
                asteroidsToRemove.push_back(a);

                // Создаем новые астероиды при разрушении
                if (asteroids[a]->getGeneration() > 1) {
                    splitAsteroid(*asteroids[a], newAsteroids);
                }

                // Начисляем очки
                score += 100 / asteroids[a]->getGeneration();
                break;
            }
        }
    }

    // 3. Удаляем столкнувшиеся объекты (с конца чтобы индексы не сдвигались)
    std::sort(bulletsToRemove.rbegin(), bulletsToRemove.rend());
    for (auto b : bulletsToRemove) {
        if (b < bullets.size()) {
            bullets.erase(bullets.begin() + b);
        }
    }

    std::sort(asteroidsToRemove.rbegin(), asteroidsToRemove.rend());
    for (auto a : asteroidsToRemove) {
        if (a < asteroids.size()) {
            asteroids.erase(asteroids.begin() + a);
        }
    }

    // 4. Добавляем новые астероиды
    asteroids.insert(asteroids.end(),
        std::make_move_iterator(newAsteroids.begin()),
        std::make_move_iterator(newAsteroids.end()));

    // 5. Проверяем столкновения корабля
    if (ship->isActive()) {
        for (const auto& asteroid : asteroids) {
            if (asteroid->isActive() && ship->checkCollision(*asteroid)) {
                handleShipCollision();
                break;
            }
        }
    }
}

void GameModel::handleShipCollision() {
    ship->loseLife();
    if (ship->getLives() <= 0) {
        gameOver = true;
    }
    else {
        ship->reset(Vector2D(width / 2, height / 2), Vector2D(0, 0));
    }
}

void GameModel::handleInput(int key, bool pressed) {
    /*
    if (gameOver) {
        if (key == 'r' && pressed) {
            resetGame();
        }
        return;
    }

    switch (key) {
    case FL_Left:
        if (pressed) ship->rotateLeft();
        break;
    case FL_Right:
        if (pressed) ship->rotateRight();
        break;
    case FL_Up:
        if (pressed) ship->startThrust();
        else ship->stopThrust();
        break;
    case ' ':
        if (pressed) fireBullet();
        break;
    }
    */
}


bool GameModel::isGameOver()
{
    return gameOver;
}

void GameModel::fireBullet() {
    if (bullets.size() < 4) {  // Limit number of bullets
        double angleRad = ship->getAngle() * M_PI / 180.0;
        Vector2D bulletPos = ship->getPosition() + Vector2D(
            ship->getSize() * cos(angleRad),
            ship->getSize() * sin(angleRad)
        );
        Vector2D bulletVel = ship->getVelocity() + Vector2D(
            5 * cos(angleRad),
            5 * sin(angleRad)
        );

        bullets.push_back(std::make_unique<Bullet>(bulletPos, bulletVel, ship->getAngle()));
    }
}
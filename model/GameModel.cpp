#include "GameModel.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

GameModel::GameModel(int w, int h) : m_width(w), m_height(h), m_score(0), m_gameOver(false) 
{
    std::srand(std::time(nullptr));
    resetGame();

    m_ship->setWrapEnabled(true);
}

void GameModel::removeOutOfBoundsObjects() 
{
    auto asteroidIt = m_asteroids.begin();
    while (asteroidIt != m_asteroids.end()) 
    {
        if ((*asteroidIt)->isOutOfBounds(m_width, m_height))
        {
            asteroidIt = m_asteroids.erase(asteroidIt);
        }
        else 
        {
            ++asteroidIt;
        }
    }

    auto bulletIt = m_bullets.begin();
    while (bulletIt != m_bullets.end()) 
    {
        if ((*bulletIt)->isOutOfBounds(m_width, m_height)) 
        {
            bulletIt = m_bullets.erase(bulletIt);
        }
        else 
        {
            ++bulletIt;
        }
    }
}

void GameModel::resetGame() 
{
    m_ship = std::make_unique<Ship>(Vector2D(m_width / 2, m_height / 2), Vector2D(0, 0), 0, 20.0);
    m_asteroids.clear();
    m_bullets.clear();
    m_score = 0;
    m_gameOver = false;
    spawnAsteroids(4);
}

void GameModel::spawnAsteroids(int count) 
{
    for (int i = 0; i < count; i++) 
    {
        double x = rand() % m_width;
        double y = rand() % m_height;
        double vx = (rand() % 100) / 100.0 * 2 - 1;
        double vy = (rand() % 100) / 100.0 * 2 - 1;
        double angle = rand() % 360;

        while (Vector2D(x, y).magnitude() < 100) 
        {
            x = rand() % m_width;
            y = rand() % m_height;
        }

        m_asteroids.push_back(std::make_unique<Asteroid>(Vector2D(x, y), Vector2D(vx, vy), angle));
    }
}

void GameModel::splitAsteroid(Asteroid& parent, std::vector<std::unique_ptr<Asteroid>>& newAsteroids) 
{
    int fragments = 2 + (rand() % 2);  // 2 или 3 фрагмента
    for (int i = 0; i < fragments; i++) 
    {
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

void GameModel::spawnAsteroid() 
{
    double x = rand() % m_width;
    double y = rand() % m_height;

    // Убедимся, что астероид не появляется слишком близко к кораблю
    while (Vector2D(x - m_ship->getPosition().getX(), y - m_ship->getPosition().getY()).magnitude() < 150) 
    {
        x = rand() % m_width;
        y = rand() % m_height;
    }

    double vx = (rand() % 100) / 100.0 * 2 - 1;  // Скорость от -1 до 1
    double vy = (rand() % 100) / 100.0 * 2 - 1;
    double angle = rand() % 360;
    int generation = 3;  // Максимальный размер

    double size = 20.0 + (rand() % 20);  // От 20 до 40px

    // Иногда создаем более мелкие астероиды
    if (rand() % 4 == 0) 
    {  // 25% chance
        size /= 1.5;
        generation = 2;
    }

    m_asteroids.push_back(std::make_unique<Asteroid>(
        Vector2D(x, y),
        Vector2D(vx, vy),
        angle,
        30.0,
        generation
    ));
}

void GameModel::update() 
{
    if (m_bulletCooldown > 0) {
        m_bulletCooldown--;
    }

    // Очищаем неактивные пули
    cleanUpBullets();
    // Обновляем состояния всех объектов
    removeOutOfBoundsObjects();

    for (auto& asteroid : m_asteroids) 
    {
        asteroid->update();
        if (asteroid->getWrapEnabled()) asteroid->wrapAround(m_width, m_height);
    }

    for (auto& bullet : m_bullets) 
    {
        bullet->update();
        if (bullet->getWrapEnabled()) bullet->wrapAround(m_width, m_height);
    }

    m_ship->update();
    if (m_ship->getWrapEnabled()) m_ship->wrapAround(m_width, m_height);

    // Обновляем оставшиеся объекты
    for (auto& asteroid : m_asteroids) asteroid->update();
    for (auto& bullet : m_bullets) bullet->update();
    m_ship->update();

    // Обработка столкновений пуль с астероидами
    std::vector<std::unique_ptr<Asteroid>> newAsteroids;
    std::vector<size_t> bulletsToRemove;
    std::vector<size_t> asteroidsToRemove;

    for (size_t b = 0; b < m_bullets.size(); ++b) 
    {
        if (!m_bullets[b]->isActive()) continue;

        for (size_t a = 0; a < m_asteroids.size(); ++a) 
        {
            if (!m_asteroids[a]->isActive()) continue;

            if (m_bullets[b]->checkCollision(*m_asteroids[a])) 
            {
                // Запоминаем индексы объектов для удаления
                bulletsToRemove.push_back(b);
                asteroidsToRemove.push_back(a);

                // Создаем новые астероиды при разрушении
                if (m_asteroids[a]->getGeneration() > 1) 
                {
                    splitAsteroid(*m_asteroids[a], newAsteroids);
                }

                // Начисляем очки
                m_score += 100 / m_asteroids[a]->getGeneration();
                break;
            }
        }
    }

    // Удаляем столкнувшиеся объекты (с конца чтобы индексы не сдвигались)
    std::sort(bulletsToRemove.rbegin(), bulletsToRemove.rend());
    for (auto b : bulletsToRemove) 
    {
        if (b < m_bullets.size()) 
        {
            m_bullets.erase(m_bullets.begin() + b);
        }
    }

    std::sort(asteroidsToRemove.rbegin(), asteroidsToRemove.rend());
    for (auto a : asteroidsToRemove) 
    {
        if (a < m_asteroids.size()) 
        {
            m_asteroids.erase(m_asteroids.begin() + a);
        }
    }

    // Добавляем новые астероиды
    m_asteroids.insert(m_asteroids.end(),
        std::make_move_iterator(newAsteroids.begin()),
        std::make_move_iterator(newAsteroids.end()));

    // Проверяем столкновения корабля
    if (m_ship->isActive()) 
    {
        for (const auto& asteroid : m_asteroids) 
        {
            if (asteroid->isActive() && m_ship->checkCollision(*asteroid)) 
            {
                handleShipCollision();
                break;
            }
        }
    }
    
}

void GameModel::handleShipCollision() 
{
    m_ship->loseLife();
    if (m_ship->getLives() <= 0) {
        m_gameOver = true;
    }
    else {
        m_ship->reset(Vector2D(m_width / 2, m_height / 2), Vector2D(0, 0));
    }
}

bool GameModel::isGameOver()
{
    return m_gameOver;
}

void GameModel::fireBullet() 
{
    if (m_bulletCooldown > 0 || m_bullets.size() >= MAX_BULLETS) {
        return;
    }

    // Создаем новую пулю
    double angleRad = m_ship->getAngle() * M_PI / 180.0;
    Vector2D bulletPos = m_ship->getPosition() + Vector2D(
        m_ship->getSize() * cos(angleRad),
        m_ship->getSize() * sin(angleRad)
    );

    Vector2D bulletVel = m_ship->getVelocity() + Vector2D(
        5 * cos(angleRad),
        5 * sin(angleRad)
    );

    m_bullets.push_back(std::make_unique<Bullet>(bulletPos, bulletVel, m_ship->getAngle()));

    // Устанавливаем перезарядку
    m_bulletCooldown = COOLDOWN_FRAMES;
}

int GameModel::getWidth() const 
{ 
    return m_width;
}

int GameModel::getHeight() const 
{ 
    return m_height; 
}

int GameModel::getScore() const
{
    return m_score;
}

bool GameModel::isGameOver() const 
{
    return m_gameOver;
}

Ship* GameModel::getShip() const 
{ 
    return m_ship.get();
}

const std::vector<std::unique_ptr<Asteroid>>& GameModel::getAsteroids() const 
{ 
    return m_asteroids; 
}

const std::vector<std::unique_ptr<Bullet>>& GameModel::getBullets() const
{
    return m_bullets;
}

void GameModel::cleanUpBullets() 
{
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](const std::unique_ptr<Bullet>& b) 
            {
                return !b->isActive();
            }),
        m_bullets.end()
    );
}

void GameModel::splitAsteroid(Asteroid& asteroid) {
    if (asteroid.getGeneration() <= 1) return;

    // Создаём 2 новых астероида меньшего размера
    for (int i = 0; i < 2; ++i) {
        double angle = rand() % 360;
        double speed = 1.0 + (rand() % 100) / 100.0; // Скорость 1.0-2.0

        Vector2D velocity(
            cos(angle * M_PI / 180.0) * speed,
            sin(angle * M_PI / 180.0) * speed
        );

        m_asteroids.push_back(std::make_unique<Asteroid>(
            asteroid.getPosition(),
            velocity,
            angle,
            asteroid.getSize() * 0.6f, // 60% от исходного размера
            asteroid.getGeneration() - 1
        ));
    }
}
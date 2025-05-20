#include "GameModel.h"
#include "Vector2D.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

GameModel::GameModel(int w, int h) : m_width(w), m_height(h), m_score(0), m_gameOver(false) 
{
    std::srand(std::time(nullptr));
    resetGame();
    m_ship->setWrapEnabled(true);
}

GameModel::~GameModel() 
{
    m_asteroids.clear();
    m_bullets.clear();
    if (m_updateThread.joinable()) 
    {
        m_updateThread.join();
    }
}
    
void GameModel::start() 
{
    m_updateThread = std::thread([this]() {
        using clock = std::chrono::steady_clock;
        const auto updateInterval = std::chrono::microseconds(1000000 / 120);

        while (!m_gameOver) {
            auto start = clock::now();
            update();
            auto end = clock::now();

            auto elapsed = end - start;
            if (elapsed < updateInterval) {
                std::this_thread::sleep_for(updateInterval - elapsed);
            }
        }
        });
}

void GameModel::stop() 
{
    m_gameOver = true;
    if (m_updateThread.joinable()) 
    {
        m_updateThread.join();
    }
}

void GameModel::removeOutOfBoundsObjects() 
{
    int i = 0;
    while(i < m_asteroids.size())
    {
        if(m_asteroids[i]->isOutOfBounds(m_width, m_height))
        {
            m_asteroids[i]->wrapAround(m_width, m_height);
        }
        else 
        {
            ++i;
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
    m_asteroids.clear();
    m_bullets.clear();
    m_bulletCooldown = 0;

    m_ship = std::make_unique<Ship>(Vector2D(m_width / 2, m_height / 2), Vector2D(0, 0), 0, 20.0);
    m_ship->setWrapEnabled(true);
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
    int fragments = 2 + (rand() % 2);
    for (int i = 0; i < fragments; i++) 
    {
        double angle = rand() % 360;
        double speed = 1.0 + (rand() % 100) / 100.0;

        Vector2D vel(
            cos(angle * M_PI / 180.0) * speed,
            sin(angle * M_PI / 180.0) * speed
        );

        newAsteroids.push_back(std::make_unique<Asteroid>(
            parent.getPosition(),
            vel,
            angle,
            parent.getSize() / (1.3 + (rand() % 40) / 100.0),
            parent.getGeneration() - 1
        ));
    }
}

void GameModel::spawnAsteroid() 
{
    double x = rand() % m_width;
    double y = rand() % m_height;

    while (Vector2D(x - m_ship->getPosition().getX(), y - m_ship->getPosition().getY()).magnitude() < 150) 
    {
        x = rand() % m_width;
        y = rand() % m_height;
    }

    double vx = (rand() % 100) / 100.0 * 2 - 1;
    double vy = (rand() % 100) / 100.0 * 2 - 1;
    double angle = rand() % 360;
    int generation = 3;

    double size = 20.0 + (rand() % 20);

    if (rand() % 4 == 0) 
    { 
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
    if (m_bulletCooldown > 0) 
    {
        m_bulletCooldown--;
    }

    cleanUpBullets();
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

    for (auto& asteroid : m_asteroids) asteroid->update();
    for (auto& bullet : m_bullets) bullet->update();
    m_ship->update();

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
                bulletsToRemove.push_back(b);
                asteroidsToRemove.push_back(a);

                if (m_asteroids[a]->getGeneration() > 1) 
                {
                    splitAsteroid(*m_asteroids[a], newAsteroids);
                }

                m_score += 100 / m_asteroids[a]->getGeneration();
                break;
            }
        }
    }

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

    m_asteroids.insert(m_asteroids.end(),
        std::make_move_iterator(newAsteroids.begin()),
        std::make_move_iterator(newAsteroids.end()));

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
    if (m_ship->getLives() <= 0) 
    {
        m_gameOver = true;
    }
    else 
    {
        m_ship->reset(Vector2D(m_width / 2, m_height / 2), Vector2D(0, 0));
    }
}

void GameModel::fireBullet() 
{
    if (m_bulletCooldown > 0 || m_bullets.size() >= MAX_BULLETS) 
    {
        return;
    }

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

bool GameModel::getGameOver() const 
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

void GameModel::splitAsteroid(Asteroid& asteroid) 
{
    if (asteroid.getGeneration() <= 1) return;

    for (int i = 0; i < 2; ++i) 
    {
        double angle = rand() % 360;
        double speed = 1.0 + (rand() % 100) / 100.0;

        Vector2D velocity(
            cos(angle * M_PI / 180.0) * speed,
            sin(angle * M_PI / 180.0) * speed
        );

        m_asteroids.push_back(std::make_unique<Asteroid>(
            asteroid.getPosition(),
            velocity,
            angle,
            asteroid.getSize() * 0.6f,
            asteroid.getGeneration() - 1
        ));
    }
}
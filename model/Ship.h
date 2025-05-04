#pragma once
#include "GameObject.h"
#include "Vector2D.h"

#define M_PI 3.14

class Ship : public GameObject
{
private:
    double m_rotationSpeed;
    double m_acceleration;
    bool m_thrusting;
    int m_lives;

public:
    Ship(Vector2D pos = Vector2D(0, 0), Vector2D vel = Vector2D(0, 0), double angle = 0, double size = 20.0)
        : GameObject(pos, vel, angle, size), m_rotationSpeed(5.0), m_acceleration(0.2), m_thrusting(false), m_lives(3) {}

    void rotateLeft();
    void rotateRight();

    void update() override;
    std::vector<Vector2D> getShape() override;
    void setThrust(bool thrust);
    int getLives() const;
    void loseLife();
    void reset(Vector2D pos, Vector2D vel);
};
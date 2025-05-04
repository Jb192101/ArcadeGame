#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
private:
    int m_lifetime;

public:
    Bullet(Vector2D pos, Vector2D vel, double angle, double size = 5.0)
        : GameObject(pos, vel, angle, size), m_lifetime(60) {}

    void update() override;

    std::vector<Vector2D> getShape() override;
};
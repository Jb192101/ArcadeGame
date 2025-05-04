#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
private:
    int lifetime;

public:
    Bullet(Vector2D pos, Vector2D vel, double angle, double size = 5.0)
        : GameObject(pos, vel, angle, size), lifetime(60) {}

    void update() override {
        GameObject::update();
        lifetime--;
        if (lifetime <= 0) {
            active = false;
        }
    }

    std::vector<Vector2D> getShape() override {
        return { position };
    }
};
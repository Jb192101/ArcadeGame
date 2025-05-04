#pragma once
#include "GameObject.h"
#include "Vector2D.h"

#define M_PI 3.14

class Ship : public GameObject
{
private:
    double rotationSpeed;
    double acceleration;
    bool thrusting;
    int lives;

public:
    Ship(Vector2D pos = Vector2D(0, 0), Vector2D vel = Vector2D(0, 0), double angle = 0, double size = 20.0)
        : GameObject(pos, vel, angle, size), rotationSpeed(5.0), acceleration(0.2), thrusting(false), lives(3) {}

    void rotateLeft() { angle -= rotationSpeed; }
    void rotateRight() { angle += rotationSpeed; }
    void startThrust() { thrusting = true; }
    void stopThrust() { thrusting = false; }

    void update() override {
        if (thrusting) {
            Vector2D thrustVec(cos(angle * M_PI / 180.0), sin(angle * M_PI / 180.0));
            velocity = velocity + thrustVec * acceleration;
        }
        GameObject::update();
    }

    std::vector<Vector2D> getShape() override {
        double angleRad = angle * M_PI / 180.0;
        std::vector<Vector2D> shape = {
            Vector2D(position.getX() + size * cos(angleRad), position.getY() + size * sin(angleRad)),
            Vector2D(position.getX() + size / 2 * cos(angleRad + 2.5), position.getY() + size / 2 * sin(angleRad + 2.5)),
            Vector2D(position.getX() + size / 3 * cos(angleRad + M_PI), position.getY() + size / 3 * sin(angleRad + M_PI)),
            Vector2D(position.getX() + size / 2 * cos(angleRad - 2.5), position.getY()  + size / 2 * sin(angleRad - 2.5))
        };
        return shape;
    }

    int getLives() const { return lives; }
    void loseLife() { lives--; }
    void reset(Vector2D pos, Vector2D vel) {
        position = pos;
        velocity = vel;
        angle = 0;
        active = true;
    }
};
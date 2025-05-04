#pragma once
#include "Vector2D.h"
#include <vector>

class GameObject {
protected:
    Vector2D position;
    Vector2D velocity;
    double angle;
    double size;
    bool active;

    bool wrapEnabled = true;

public:
    GameObject(Vector2D pos, Vector2D vel, double angle, double size)
        : position(pos), velocity(vel), angle(angle), size(size), active(true) {}

    virtual ~GameObject() = default;

    void setWrapEnabled(bool enabled) {
        wrapEnabled = enabled;
    }
        
    virtual void update() {
        position = position + velocity;
    }

    virtual void wrapAround(int width, int height) {
        if (position.getX() < 0) position.setX(width + size);
        if (position.getX() > width) position.setX(position.getX() - size);
        if (position.getY() < 0) position.setY(height + size);
        if (position.getY() > height) position.setY(position.getY() - size);
    }

    virtual std::vector<Vector2D> getShape() = 0;

    Vector2D getPosition() { return position; }
    Vector2D getVelocity() { return velocity; }
    double getAngle() const { return angle; }
    double getSize() const { return size; }
    bool isActive() const { return active; }
    void setActive(bool a) { active = a; }

    bool checkCollision(GameObject& other) const {
        if (!active || !other.active) return false; // Проверка активности
        Vector2D diff = position - other.position;
        double distance = diff.magnitude();
        return distance < (size + other.size);
    }

    virtual bool isOutOfBounds(int screenWidth, int screenHeight) {
        return position.getX() < -size * 2 || position.getX() > screenWidth + size * 2 ||
            position.getY() < -size * 2 || position.getY() > screenHeight + size * 2;
    }

    bool getWrapEnabled()
    {
        return wrapEnabled;
    }
};
#pragma once
#include "Vector2D.h"
#include <vector>

class GameObject
{
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    double m_angle;
    double m_size;
    bool m_active;

    bool m_wrapEnabled = true;

public:
    GameObject(Vector2D pos, Vector2D vel, double angle, double size)
        : m_position(pos), m_velocity(vel), m_angle(angle), m_size(size), m_active(true) {}

    virtual ~GameObject() = default;

    void setWrapEnabled(bool enabled);
        
    virtual void update();

    virtual void wrapAround(int width, int height);

    virtual std::vector<Vector2D> getShape() = 0;

    Vector2D getPosition();
    Vector2D getVelocity();
    double getAngle() const;
    double getSize() const;
    bool isActive() const;
    void setActive(bool a);
    bool getWrapEnabled();

    bool checkCollision(GameObject& other) const;

    virtual bool isOutOfBounds(int screenWidth, int screenHeight);
};
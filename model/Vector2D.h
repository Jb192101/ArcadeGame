#pragma once

#include <cmath>

class Vector2D {
private:
    double m_x;
    double m_y;
public:
    Vector2D(double x = 0, double y = 0) : m_x(x), m_y(y) {}

    Vector2D operator+(Vector2D& other) const {
        return Vector2D(m_x + other.getX(), m_y + other.getY());
    }

    double getX() { return m_x; }
    double getY() { return m_y; }
    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }

    Vector2D operator-(Vector2D& other) const {
        return Vector2D(m_x - other.getX(), m_y - other.getY());
    }

    Vector2D operator*(double scalar) const {
        return Vector2D(m_x * scalar, m_y * scalar);
    }

    double magnitude() const {
        return sqrt(m_x * m_x + m_y * m_y);
    }

    Vector2D normalize() const {
        double mag = magnitude();
        if (mag > 0) {
            return Vector2D(m_x / mag, m_y / mag);
        }
        return Vector2D(0, 0);
    }
};
#pragma once

#include <cmath>

class Vector2D 
{
private:
    double m_x;
    double m_y;
public:
    Vector2D(double x = 0, double y = 0) : m_x(x), m_y(y) {}

    double getX();
    double getY();
    void setX(double x);
    void setY(double y);

    Vector2D operator+(Vector2D& other) const;
    Vector2D operator-(Vector2D& other) const;
    Vector2D operator*(double scalar) const;

    double magnitude() const;

    Vector2D normalize() const;
};
#include "Vector2D.h"

Vector2D Vector2D::operator+(Vector2D& other) const
{
    return Vector2D(m_x + other.getX(), m_y + other.getY());
}

double Vector2D::getX() 
{ 
    return m_x; 

}
double Vector2D::getY() 
{ 
    return m_y; 
}

void Vector2D::setX(double x)
{ 
    m_x = x;
}

void Vector2D::setY(double y) 
{ 
    m_y = y; 
}

Vector2D Vector2D::operator-(Vector2D& other) const 
{
    return Vector2D(m_x - other.getX(), m_y - other.getY());
}

Vector2D Vector2D::operator*(double scalar) const
{
    return Vector2D(m_x * scalar, m_y * scalar);
}

double Vector2D::magnitude() const
{
    return sqrt(m_x * m_x + m_y * m_y);
}

Vector2D Vector2D::normalize() const
{
    double mag = magnitude();
    if (mag > 0) 
    {
        return Vector2D(m_x / mag, m_y / mag);
    }
    return Vector2D(0, 0);
}
#include "Ship.h"

void Ship::rotateLeft() 
{ 
    m_angle -= m_rotationSpeed; 
}

void Ship::rotateRight()
{ 
    m_angle += m_rotationSpeed;
}

void Ship::setThrust(bool thrust)
{ 
    m_thrusting = thrust;
}

void Ship::update()
{
    if (m_thrusting) 
    {
        Vector2D thrustVec(cos(m_angle * M_PI / 180.0), sin(m_angle * M_PI / 180.0));
        m_velocity = m_velocity + thrustVec * m_acceleration * 0.2;
    }
    GameObject::update();
}

std::vector<Vector2D> Ship::getShape()
{
    double angleRad = m_angle * M_PI / 180.0;
    std::vector<Vector2D> shape = {
        Vector2D(m_position.getX() + m_size * cos(angleRad), m_position.getY() + m_size * sin(angleRad)),
        Vector2D(m_position.getX() + m_size / 2 * cos(angleRad + 2.5), m_position.getY() + m_size / 2 * sin(angleRad + 2.5)),
        Vector2D(m_position.getX() + m_size / 3 * cos(angleRad + M_PI), m_position.getY() + m_size / 3 * sin(angleRad + M_PI)),
        Vector2D(m_position.getX() + m_size / 2 * cos(angleRad - 2.5), m_position.getY() + m_size / 2 * sin(angleRad - 2.5))
    };
    return shape;
}

int Ship::getLives() const
{ 
    return m_lives;
}

void Ship::loseLife()
{ 
    m_lives--;
}

void Ship::reset(Vector2D pos, Vector2D vel) 
{
    m_position = pos;
    m_velocity = vel;
    m_angle = 0;
    m_active = true;
}
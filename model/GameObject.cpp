#include "GameObject.h"

void GameObject::setWrapEnabled(bool enabled) 
{
    m_wrapEnabled = enabled;
}

void GameObject::update() 
{
    m_position = m_position + m_velocity;
}

void GameObject::wrapAround(int width, int height) 
{
    // if (m_position.getX() < 0) m_position.setX(width + m_size);
    // if (m_position.getX() > width) m_position.setX(m_size);
    // if (m_position.getY() < 0) m_position.setY(height + m_size);
    // if (m_position.getY() > height) m_position.setY(m_size);
    if (m_position.getX() < -m_size) m_position.setX(width);
    if (m_position.getX() > width + m_size) m_position.setX(0);
    if (m_position.getY() < -m_size) m_position.setY(height);
    if (m_position.getY() > height + m_size) m_position.setY(0);
}

Vector2D GameObject::getPosition() 
{ 
    return m_position;
}

Vector2D GameObject::getVelocity()
{ 
    return m_velocity; 
}

double GameObject::getAngle() const 
{ 
    return m_angle; 
}

double GameObject::getSize() const
{
    return m_size;
}

bool GameObject::isActive() const 
{ 
    return m_active; 
}

void GameObject::setActive(bool a) 
{ 
    m_active = a;
}

bool GameObject::checkCollision(GameObject& other) const 
{
    if (!m_active || !other.m_active) return false;
    Vector2D diff = m_position - other.m_position;
    double distance = diff.magnitude();
    return distance < (m_size + other.m_size);
}

bool GameObject::isOutOfBounds(int screenWidth, int screenHeight) 
{
    return m_position.getX() < -m_size * 2 || m_position.getX() > screenWidth + m_size * 2 ||
        m_position.getY() < -m_size * 2 || m_position.getY() > screenHeight + m_size * 2;
}

bool GameObject::getWrapEnabled()
{
    return m_wrapEnabled;
}
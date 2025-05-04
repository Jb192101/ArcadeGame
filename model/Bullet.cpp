#include "Bullet.h"

void Bullet::update() 
{
    GameObject::update();
    m_lifetime--;
    if (m_lifetime <= 0) 
    {
        m_active = false;
    }
}

std::vector<Vector2D> Bullet::getShape()
{
    return { m_position };
}
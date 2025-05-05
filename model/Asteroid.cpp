#include "Asteroid.h"

void Asteroid::createRandomShape()
{
    m_vertices.clear();
    int numVertices = 8 + rand() % 5;
    for (int i = 0; i < numVertices; i++) 
    {
        double angle = 2 * M_PI * i / numVertices;
        double radius = m_size * (0.7 + 0.3 * (rand() % 100) / 100.0);
        m_vertices.emplace_back(radius * cos(angle), radius * sin(angle));
    }
}

std::vector<Vector2D> Asteroid::getShape()
{
    std::vector<Vector2D> shape;
    for (auto& vertex : m_vertices) {
        double x = m_position.getX() + vertex.getX() * cos(m_angle * M_PI / 180.0) - vertex.getY() * sin(m_angle * M_PI / 180.0);
        double y = m_position.getY() + vertex.getX() * sin(m_angle * M_PI / 180.0) + vertex.getY() * cos(m_angle * M_PI / 180.0);
        shape.emplace_back(x, y);
    }
    return shape;
}

int Asteroid::getGeneration() const 
{ 
    return m_generation;
}
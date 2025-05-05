#pragma once
#include "HostilyEntity.h"
#include <vector>

class Asteroid : public HostilyEntity {
private:
    int m_generation;
    std::vector<Vector2D> m_vertices;

public:
    Asteroid(Vector2D pos = Vector2D(0, 0), Vector2D vel = Vector2D(0, 0),
        double angle = 0, double size = 30.0, int generation = 3)
        : HostilyEntity(pos, vel, angle, size), m_generation(generation) {
        createRandomShape();
    }

    void createRandomShape();

    std::vector<Vector2D> getShape() override;
    int getGeneration() const;
};
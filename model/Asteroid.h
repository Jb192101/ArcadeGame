#pragma once
#include "GameObject.h"
#include <vector>

class Asteroid : public GameObject {
private:
    int generation;
    std::vector<Vector2D> vertices;

public:
    Asteroid(Vector2D pos = Vector2D(0, 0), Vector2D vel = Vector2D(0, 0),
        double angle = 0, double size = 30.0, int generation = 3)
        : GameObject(pos, vel, angle, size), generation(generation) {
        createRandomShape();
    }

    void createRandomShape() {
        vertices.clear();
        int numVertices = 8 + rand() % 5;
        for (int i = 0; i < numVertices; i++) {
            double angle = 2 * M_PI * i / numVertices;
            double radius = size * (0.7 + 0.3 * (rand() % 100) / 100.0);
            vertices.emplace_back(radius * cos(angle), radius * sin(angle));
        }
    }

    std::vector<Vector2D> getShape() override {
        std::vector<Vector2D> shape;
        for (auto& vertex : vertices) {
            double x = position.getX() + vertex.getX() * cos(angle * M_PI / 180.0) - vertex.getY() * sin(angle * M_PI / 180.0);
            double y = position.getY()  + vertex.getX() * sin(angle * M_PI / 180.0) + vertex.getY() * cos(angle * M_PI / 180.0);
            shape.emplace_back(x, y);
        }
        return shape;
    }

    int getGeneration() const { return generation; }
};
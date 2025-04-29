#include "AsteroidModel.h"
# define M_PI           3.14159265358979323846

AsteroidModel::AsteroidModel(Vector2D pos, Size size)
{
	this->position = pos;
	this->size = size;

	std::srand(std::time(nullptr));

    float speed = 0.0f;
    switch (size) {
    case LARGE: speed = 1.0f + (std::rand() % 10) / 10.0f; break;
    case MEDIUM: speed = 1.5f + (std::rand() % 10) / 10.0f; break;
    case SMALL: speed = 2.0f + (std::rand() % 10) / 10.0f; break;
    }

    angle = std::rand() % 360;
    rotationSpeed = (std::rand() % 10 - 5) / 10.0f;

    float radians = angle * (M_PI / 180.0f);

    velocity.setX(std::sin(radians) * speed);
    velocity.setY(-std::cos(radians) * speed);

    // Заготовка точек для будущей отрисовки
    int points = 8 + std::rand() % 5;
    float radius = 0.0f;

    switch (size) {
    case LARGE: radius = 30.0f; break;
    case MEDIUM: radius = 15.0f; break;
    case SMALL: radius = 7.0f; break;
    }

    for (int i = 0; i < points; ++i) {
        float angle = 2 * M_PI * i / points;
        float variation = 0.7f + (std::rand() % 6) / 10.0f;
        shape.emplace_back(radius * variation * std::cos(angle),
            radius * variation * std::sin(angle));
    }
}

void AsteroidModel::Update(float deltaTime, int w, int h)
{
    position += velocity * deltaTime;
    rotation += rotationSpeed * deltaTime;

	// В классе GameModel реализуй, что если астероид вышел за границы, то всё нормально
}

float AsteroidModel::sizeAtFloat()
{
    float sizeFloat;
    switch (size)
    {
    case SMALL:
        sizeFloat = 0.25f;
        break;
    case MEDIUM:
        sizeFloat = 0.5f;
        break;
    case LARGE:
        sizeFloat = 1.0f;
        break;
    }

    return sizeFloat;
}
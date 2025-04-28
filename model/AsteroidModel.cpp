// AsteroidModel.cpp
#include "AsteroidModel.h"
# define M_PI           3.14159265358979323846

AsteroidModel::AsteroidModel(float startX, float startY, Size size)
    : x(startX), y(startY), size(size), rotation(0) {
    // Инициализация случайных значений
    std::srand(std::time(nullptr));

    // Установка скорости в зависимости от размера
    float speed = 0.0f;
    switch (size) {
    case LARGE: speed = 1.0f + (std::rand() % 10) / 10.0f; break;
    case MEDIUM: speed = 1.5f + (std::rand() % 10) / 10.0f; break;
    case SMALL: speed = 2.0f + (std::rand() % 10) / 10.0f; break;
    }

    angle = std::rand() % 360;
    rotationSpeed = (std::rand() % 10 - 5) / 10.0f;

    // Преобразуем угол в радианы
    float radians = angle * (M_PI / 180.0f);

    // Устанавливаем скорость
    velocityX = std::sin(radians) * speed;
    velocityY = -std::cos(radians) * speed;

    // Создаем форму астероида
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

void AsteroidModel::Update() {
    x += velocityX;
    y += velocityY;
    rotation += rotationSpeed;
}

bool AsteroidModel::CheckCollisions(float otherX, float otherY, float otherRadius) const {
    float dx = x - otherX;
    float dy = y - otherY;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (GetCollisionRadius() + otherRadius);
}

float AsteroidModel::GetCollisionRadius() const {
    switch (size) {
    case LARGE: return 30.0f;
    case MEDIUM: return 15.0f;
    case SMALL: return 7.0f;
    default: return 0.0f;
    }
}

void AsteroidModel::SetVelocity(float v1, float v2) {
    this->velocityX = v1;
    this->velocityY = v2;
}
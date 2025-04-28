// SpaceShipModel.cpp
#include "SpaceShipModel.h"
# define M_PI           3.14159265358979323846

SpaceShipModel::SpaceShipModel(float startX, float startY)
    : x(startX), y(startY), velocityX(0), velocityY(0), angle(0),
    acceleration(0.2f), maxSpeed(5.0f), rotationSpeed(5.0f) {}

void SpaceShipModel::Update() {
    // Обновление позиции на основе скорости
    x += velocityX;
    y += velocityY;

    // Ограничение максимальной скорости
    float speed = std::sqrt(velocityX * velocityX + velocityY * velocityY);
    if (speed > maxSpeed) {
        velocityX = (velocityX / speed) * maxSpeed;
        velocityY = (velocityY / speed) * maxSpeed;
    }

    // Небольшое замедление (трение)
    velocityX *= 0.98f;
    velocityY *= 0.98f;
}

void SpaceShipModel::RotateLeft() {
    angle -= rotationSpeed;
}

void SpaceShipModel::RotateRight() {
    angle += rotationSpeed;
}

void SpaceShipModel::Accelerate() {
    // Преобразование угла в радианы
    float radians = angle * (M_PI / 180.0f);

    // Ускорение в направлении угла
    velocityX += std::sin(radians) * acceleration;
    velocityY -= std::cos(radians) * acceleration;
}

void SpaceShipModel::Decelerate() {
    // Замедление (обратное ускорение)
    float radians = angle * (M_PI / 180.0f);
    velocityX -= std::sin(radians) * acceleration * 0.5f;
    velocityY += std::cos(radians) * acceleration * 0.5f;
}

bool SpaceShipModel::CheckCollisions(float otherX, float otherY, float otherRadius) const {
    float dx = x - otherX;
    float dy = y - otherY;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (GetCollisionRadius() + otherRadius);
}
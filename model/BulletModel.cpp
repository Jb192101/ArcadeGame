// BulletModel.cpp
#include "BulletModel.h"
# define M_PI           3.14159265358979323846

BulletModel::BulletModel(float startX, float startY, float angle)
    : x(startX), y(startY), angle(angle), speed(10.0f), lifetime(30) {
    // Преобразуем угол в радианы
    float radians = angle * (M_PI / 180.0f);

    // Устанавливаем скорость
    velocityX = std::sin(radians) * speed;
    velocityY = -std::cos(radians) * speed;
}

void BulletModel::Update() {
    x += velocityX;
    y += velocityY;
    lifetime--;
}

bool BulletModel::CheckCollisions(float otherX, float otherY, float otherRadius) const {
    float dx = x - otherX;
    float dy = y - otherY;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (GetCollisionRadius() + otherRadius);
}
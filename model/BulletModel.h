// BulletModel.h
#pragma once
#include "Model.h"
#include <cmath>

class BulletModel : public Model {
private:
    float x, y;            // Позиция
    float velocityX, velocityY; // Скорость
    float angle;           // Угол движения
    float speed;           // Скорость пули
    int lifetime;          // Время жизни в кадрах

public:
    BulletModel(float startX, float startY, float angle);

    void Update() override;
    bool IsExpired() const { return lifetime <= 0; }

    // Геттеры
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetAngle() const { return angle; }

    bool CheckCollisions(float x, float y, float radius) const override;
    float GetCollisionRadius() const { return 2.0f; }
};
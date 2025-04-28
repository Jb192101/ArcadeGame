// BulletModel.h
#pragma once
#include "Model.h"
#include <cmath>

class BulletModel : public Model {
private:
    float x, y;            // �������
    float velocityX, velocityY; // ��������
    float angle;           // ���� ��������
    float speed;           // �������� ����
    int lifetime;          // ����� ����� � ������

public:
    BulletModel(float startX, float startY, float angle);

    void Update() override;
    bool IsExpired() const { return lifetime <= 0; }

    // �������
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetAngle() const { return angle; }

    bool CheckCollisions(float x, float y, float radius) const override;
    float GetCollisionRadius() const { return 2.0f; }
};
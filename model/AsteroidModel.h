// AsteroidModel.h
#pragma once
#include "Model.h"
#include <cmath>
#include <vector>

#include <cstdlib>
#include <ctime>

class AsteroidModel : public Model {
public:
    enum Size { LARGE, MEDIUM, SMALL };

private:
    float x, y;            // �������
    float velocityX, velocityY; // ��������
    float angle;           // ���� ��������
    float rotation;        // ��������
    float rotationSpeed;   // �������� ��������
    Size size;             // ������
    std::vector<std::pair<float, float>> shape; // ����� ���������

public:
    AsteroidModel(float startX, float startY, Size size);

    void Update() override;
    Size GetSize() const { return size; }

    // �������
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetAngle() const { return angle; }
    float GetRotation() const { return rotation; }
    const std::vector<std::pair<float, float>>& GetShape() const { return shape; }

    void SetVelocity(float v1, float v2);

    bool CheckCollisions(float x, float y, float radius) const override;
    float GetCollisionRadius() const;
};
#pragma once
#include "Model.h"
#include <cmath>

class SpaceShipModel : public Model {
private:
    float x, y;        // �������
    float velocityX, velocityY; // ��������
    float angle;        // ���� ��������
    float acceleration; // ���������
    float maxSpeed;     // ������������ ��������
    float rotationSpeed; // �������� ��������

public:
    SpaceShipModel(float startX, float startY);

    void Update() override;

    // ����������
    void RotateLeft();
    void RotateRight();
    void Accelerate();
    void Decelerate();

    // �������
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetAngle() const { return angle; }
    float GetVelocityX() const { return velocityX; }
    float GetVelocityY() const { return velocityY; }

    // �������
    void SetPosition(float newX, float newY) { x = newX; y = newY; }
    void SetVelocity(float newVX, float newVY) { velocityX = newVX; velocityY = newVY; }

    bool CheckCollisions(float x, float y, float radius) const override;
    float GetCollisionRadius() const { return 15.0f; }
};
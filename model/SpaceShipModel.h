#pragma once
#include "Model.h"
#include "BulletModel.h"
#include <cmath>

class SpaceShipModel : public Model
{
private:
    float thrustPower; // ���� ���������
    bool thrusting; // �������� �� ���������?
    float invincibilityTime; // �����, � ������� ������� ���������� �����
    float rotation; // �������� �������
public:
    SpaceShipModel(Vector2D pos);

    bool isInvincible() const;
    BulletModel shoot();
    void setThrusting(bool isThrusting);
    void rotate(float angle);
    void Update(float deltaTime, int w, int h) override;

    float getInvincibilityTime() { return invincibilityTime; };
    void setInvincibilityTime(float it) { this->invincibilityTime = it; };
};
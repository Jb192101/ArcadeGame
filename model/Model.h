/*
* Model - ����������� ����� ��� ���� ������� �� model (����� GameModel)
*/
#pragma once

#include "Vector2D.h"

class Model
{
protected:
    Vector2D position;
    Vector2D velocity;
public:
    virtual ~Model() = default;
    virtual void Update(float deltaTime, int w, int h) = 0; // w - ������ ����, h - ������ ����

    Vector2D getPosition() { return position; };
    Vector2D getVelocity() { return velocity; };
};

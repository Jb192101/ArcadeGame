/*
* Model - абстрактный класс для всех классов из model (кроме GameModel)
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
    virtual void Update(float deltaTime, int w, int h) = 0; // w - ширина окна, h - высота окна

    Vector2D getPosition() { return position; };
    Vector2D getVelocity() { return velocity; };
};

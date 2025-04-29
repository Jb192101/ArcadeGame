#pragma once
#include "HostileEntity.h"
#include "Vector2D.h"
#include "Size.c"

#include <vector>
#include <ctime>

class AsteroidModel : public HostileEntity
{
private:
    float rotation;
    float rotationSpeed;
    float angle;
    std::vector<std::pair<float, float>> shape; // возможно, придётся убрать

public:
    AsteroidModel(Vector2D pos, Size size);
    void Update(float deltaTime, int w, int h) override;

    float sizeAtFloat();
};
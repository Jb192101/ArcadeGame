// Model.h - Базовый класс модели
#pragma once

class Model {
public:
    virtual ~Model() = default;
    virtual void Update() = 0;
    virtual bool CheckCollisions(float x, float y, float radius) const = 0;
};

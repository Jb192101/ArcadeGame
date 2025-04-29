// BulletModel.h
#pragma once
#include "Model.h"
#include <cmath>

class BulletModel : public Model
{
private:
	float lifetime;
public:
	BulletModel(Vector2D pos, Vector2D vel, float lifetime);

	void Update(float deltaTime, int w, int h) override;

	bool isAlive() const;
};
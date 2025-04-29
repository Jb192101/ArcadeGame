// BulletModel.cpp
#include "BulletModel.h"
# define M_PI           3.14159265358979323846

BulletModel::BulletModel(Vector2D pos, Vector2D vel, float lifetime)
{
	this->position = pos;
	this->velocity = vel;

	this->lifetime = lifetime;
}
	
bool BulletModel::isAlive() const
{
	return lifetime > 0;
}

void BulletModel::Update(float deltaTime, int w, int h)
{
    position += velocity * deltaTime;
    lifetime -= deltaTime;

    // Потом в GameModel реализуй механизм выхода лазера за пределы окна
}
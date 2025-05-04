#pragma once

/*
Класс для возможного создания в будущем бонусных объектов
*/

#include "GameObject.h"

class HostilyEntity : public GameObject
{
public:
	HostilyEntity(Vector2D pos, Vector2D vel, double angle, double size) : GameObject(pos, vel, angle, size) {};
};
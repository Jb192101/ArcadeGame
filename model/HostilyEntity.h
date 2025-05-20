#pragma once

#include "GameObject.h"

class HostilyEntity : public GameObject
{
public:
	HostilyEntity(Vector2D pos, Vector2D vel, double angle, double size) : GameObject(pos, vel, angle, size) {};
};
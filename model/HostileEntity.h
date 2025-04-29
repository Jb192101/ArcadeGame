#pragma once

#include "Model.h"

/*
Класс HostileEntity на случай, если понадобится создавать бонусные сущности
*/

class HostileEntity : public Model
{
protected:
	Size size;
public:
	Size getSize() { return size; };
};

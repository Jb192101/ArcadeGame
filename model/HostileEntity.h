#pragma once

#include "Model.h"

/*
����� HostileEntity �� ������, ���� ����������� ��������� �������� ��������
*/

class HostileEntity : public Model
{
protected:
	Size size;
public:
	Size getSize() { return size; };
};

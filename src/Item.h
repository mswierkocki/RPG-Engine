#pragma once

#include "Object.h"

class Item : public Object
{
protected:
	int value; //exemplary
	int count; //same here
public:
	Item(int value = 0, int count = 0);

	//Item Copy(float x = 0, float y = 0, int count = 1);

	void Update(double deltaTime);
};

#pragma once

#include "Object.h"

class Creature : public Object
{
protected:
	float dx,dy;

public:
	Creature(float dx = 0, float dy = 0);
	
	//Creature Copy(float x = 0, float y = 0, int dir = 0, float dx = 0, float dy = 0);

	void Update(double deltaTime);
};

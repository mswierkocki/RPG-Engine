#include "Creature.h"

Creature::Creature(float dx, float dy):Object(),dx(dx),dy(dy)
{
}

//Creature Creature::Copy(float x, float y, int dir, float dx, float dy)
//{
//	Creature copy = *this;
//	
//	copy.x = x;
//	copy.y = y;
//	copy.dx = dx;
//	copy.dy = dy;
//
//	return copy;
//}

void Creature::Update(double deltaTime)
{
	animations[animation]->Update(deltaTime);
	x += (int)(dx * deltaTime);
	y += (int)(dy * deltaTime);
}

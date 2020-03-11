#pragma once

#include "Creature.h"

class Player
{
private:
	Creature* avatar;
public:
	Player(){}
	Player(Creature* c);
};

#pragma once
#include "Window.h"
#include "Engine.h"
#include "GameObjectManager.h"

class World :public Window
{
private:
	int a;
	GameObjectManager* gom;
    Engine *engine;
public:
	World(GameObjectManager* gom,Engine* eng);
	int color;
	void Update(double deltaTime);
	void Draw();
};


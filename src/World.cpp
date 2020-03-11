#include "World.h"
#include "Event.h"
#include <iostream>
#include "utils.h"
using namespace Input;

World::World(GameObjectManager* gom, Engine *eng):gom(gom),engine(eng),a(0)
{
	type = WINDOWS_TYPE::GAME_WORLD_WINDOWS;
	engine->SetCurrentMap(0);
	engine->ResetZoom();
	engine->Zoom(2);
}

void World::Update(double deltaTime)
{
	float speed = 0.01f;
	engine->Update(deltaTime);

	if(isDown(MoveDown))
	{
		engine->MoveMap(Pointf(0,-speed));
	}
	if(isDown(MoveRight))
	{
		engine->MoveMap(Pointf(speed,0));
	}
	if(isDown(MoveLeft))
	{
		engine->MoveMap(Pointf(-speed,0));
	}
	if(isDown(MoveUp))
	{
		engine->MoveMap(Pointf(0,speed));
	}


	if(isDown(toggleSkillsMenu))          
	{
		eventQueue.push_back(new SetVisibleEvent(WINDOWS_TYPE::INTERFACE_WINDOWS,BOOL_TYPE::SET_OPPOSITE));
	}
	if(isDown(ESC))
	{
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::PAUSE_WINDOWS));
		eventQueue.push_back(new SetActiveEvent(WINDOWS_TYPE::GAME_WORLD_WINDOWS,BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new SetActiveEvent(WINDOWS_TYPE::INTERFACE_WINDOWS,BOOL_TYPE::SET_FALSE));
	}

	if(a > 200) a = 0;
	a += 10;
}

void World::Draw()
{	
	if(engine->HasMap()){

		engine->DrawMap();
		engine->DrawObjects();
}
	else{

	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f, 0.0f, 0.0f);   
		glVertex3f(0.0f, 150.0f, 0.0f);    
		glVertex3f( 50.0f, (float)a, 0.0f);    
	glEnd();
	}
}

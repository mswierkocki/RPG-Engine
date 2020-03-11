#pragma once

#define MEASURE_FUNC(func) Timer::Start(); func; Timer::Stop(); std::cout << "Czas: " << Timer::GetTime() << "s." << std::endl;

//#include <iostream>
#include <sstream>

#include "OutputManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "GameObjectManager.h"
////
#include "GameEvent.h"
#include "GL/glfw.h"
////
#include "Window.h"
#include "Interface.h"
#include "World.h"
#include "MainMenuWindows.h"
#include "Pause.h"
#include "EdytorWindow.h"
#include "ObjectWindow.h"
#include "NewAnim.h"
#include "SelectTexture.h"
#include "NewTexture.h"
#include "OldTexture.h"
#include "SelectMap.h"
#include "NewMap.h"
#include "OldMap.h"
#include "OldObject.h"
#include "AskWindow.h"
#include "SaveWindow.h"
////
#include "Event.h"
#include "error.h"
#include "utils.h"

#include "xml/iniparser.h"
/////


/*
Silnik ca³ej gry
*/
class GameManager{

private:
	OutputManager *outputManager;
	SoundManager *soundManager;
	GameObjectManager *gameObjectManager;
	GameEvent *gameendEvent;
	Engine *engine;
	IniParser cfg;	
	
	
public:
	bool isEnd;
	
	GameManager():isEnd(false)
	{
	//	gameendEvent = new GameEvent(nullptr,nullptr);
	//	InputManager::mapToKey(gameendEvent,GLFW_KEY_ENTER);
		outputManager = new OutputManager();
		if(!LoadSettings())
			error("reading settings!");

		message("Creating scene");
		MEASURE_FUNC(outputManager->CreateScene())
		message("Creating SoundManager");
		MEASURE_FUNC(soundManager = new SoundManager())
		message("Creating GOM");
		MEASURE_FUNC(gameObjectManager = new GameObjectManager())
		message("Creating Engine");
		MEASURE_FUNC(engine = new Engine(gameObjectManager))
		message("Creating MainMenu");
		MEASURE_FUNC(windowsQueue.push_back(new MainMenuWindows()))
		Controlka::Init();
		TextControl::Init();
		Map::Init();
	}
	~GameManager()
	{
		delete gameObjectManager;
		delete engine;
		delete outputManager;
		delete soundManager;

	}
	void run (double deltaTime);
	OutputManager* getOutputManager();
	bool LoadSettings();
};


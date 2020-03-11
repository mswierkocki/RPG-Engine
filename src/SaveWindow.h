#pragma once
#include "window.h"
#include "GameObjectManager.h"
#include "Engine.h"
#include "Button.h"
#include "TextControl.h"

class SaveWindow :public Window
{
private:
	GameObjectManager* gom;
	Engine* engine;

	Button* backButton;
	Button* newSaveButton;
	Button* overSaveButton;
	Button* cancleButton;
	TextControl* name;
	bool* wynik;

public:
	SaveWindow(GameObjectManager* gom, Engine* engine, bool* wynik);

	void Draw();
	void Update(double deltaTime);

};


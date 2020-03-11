#pragma once
#include "window.h"
#include "Button.h"
#include "Texture.h"
#include "TextControl.h"
#include "GameObjectManager.h"
#include "Engine.h"

class SelectMap :public Window
{
private:
	Button* autoSaveMapa;
	Button* nowaMapa;
	Button* wczytajMape;
	Button* backButton;
	Button* okButton;
	TextControl* idText;

	Texture* bg;

	GameObjectManager* gom;
	Engine* engine;
	int mapId;

public:
	SelectMap(GameObjectManager* gom, Engine* engine);
	void Draw();
	void Update(double deltaTime);
};


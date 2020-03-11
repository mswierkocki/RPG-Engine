#pragma once
#include "window.h"
#include "Texture.h"
#include "GameObjectManager.h"
#include "Button.h"
#include "SelectControl.h"
#include "FieldControl.h"
#include "Event.h"
#include "Engine.h"

class OldObject :public Window
{
private:
	GameObjectManager* gom;
	Engine* engine;

	Button* addButton;
	Button* editButton;
	Button* backButton;
	Button* delButton;
	SelectControl* select;
	FieldControl* field;

	link<Object> object;

	bool editWindow;

	int objectId;

public:
	OldObject(GameObjectManager* gom, Engine* engine);

	void Draw();
	void Update(double deltaTime);
};


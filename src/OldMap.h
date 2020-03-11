#pragma once
#include "window.h"
#include "Texture.h"
#include "GameObjectManager.h"
#include "Button.h"
#include "SelectControl.h"
#include "FieldControl.h"
#include "Event.h"

class OldMap :public Window
{
private:
	GameObjectManager* gom;
	
	Button* okButton;
	Button* backButton;
	Button* delButton;
	SelectControl* select;
	FieldControl* field;

	int* mapId;
	int id;

public:
	OldMap(GameObjectManager* gom, int* id);

	void Draw();
	void Update(double deltaTime);

};


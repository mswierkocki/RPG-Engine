#pragma once
#include "window.h"
#include "Texture.h"
#include "GameObjectManager.h"
#include "Button.h"
#include "SelectControl.h"
#include "FieldControl.h"
#include "Event.h"
#include "TextControl.h"

class OldTexture :public Window
{
private:
	GameObjectManager* gom;

	Button* okButton;
	Button* backButton;
	Button* delButton;
	Button* importButton;
	Button* searchButton;
	SelectControl* select;
	FieldControl* field;
	TextControl* filtr;


	bool newTextureWindow;
	
	vector<int> maping;

	Texture* tex;
	int* id;

public:
	OldTexture(GameObjectManager* gom, int* id);

	void Draw();
	void Update(double deltaTime);
};


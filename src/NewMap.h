#pragma once
#include "window.h"
#include "Button.h"
#include "TextControl.h"
#include "GameObjectManager.h"
#include "Texture.h"
#include "FieldControl.h"

class NewMap :public Window
{
private:
	GameObjectManager* gom;
	Button* okButton;
	Button* backButton;
	Button* lButton;
	Button* rButton;
	TextControl* widthBox;
	TextControl* heightBox;
	TextControl* nameBox;
	FieldControl* baseField;

	int base;
	int maxBase; 

	link<Map>& map;

public:
	NewMap(GameObjectManager* gom, link<Map>* map);
	void Draw();
	void Update(double deltaTime);
};


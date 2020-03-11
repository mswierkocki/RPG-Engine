#pragma once
#include "Window.h"
#include "Button.h"
#include "TextControl.h"
#include "GameObjectManager.h"
#include "Texture.h"

class NewTexture :public Window
{
private:
	GameObjectManager* gom;
	Button* openButton;
	Button* saveButton;
	Button* okButton;
	Button* backButton;
	TextControl* path;
	TextControl* name;
	string srcPath;
	string desPath;
	int* id;

public:
	NewTexture(GameObjectManager* gom, int* id);

	void Draw();
	void Update(double deltaTime);
};


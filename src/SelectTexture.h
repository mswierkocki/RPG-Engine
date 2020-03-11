#pragma once
#include "window.h"
#include "Texture.h"
#include "GameObjectManager.h"
#include "Button.h"
#include "FieldControl.h"
#include "Event.h"

class SelectTexture :public Window
{
private:
	GameObjectManager* gom;
	Button* okButton;
	Button* backButton;
	Button* newButton;
	Button* oldButton;
	FieldControl* field;

	int* textureId;

public:
	SelectTexture(GameObjectManager* gom, int* id);

	void Draw();
	void Update(double deltaTime);
};


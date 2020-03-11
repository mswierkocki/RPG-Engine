#pragma once
#include "window.h"
#include "TextControl.h"
#include "Texture.h"
#include "Button.h"
#include "FieldControl.h"
#include "GameObjectManager.h"

class NewAnim :public Window
{
private:
	GameObjectManager* gom;
	TextControl* textureId;
	TextControl* frameCount;
	TextControl* elapseTime;
	TextControl* name;
	Button* okButton;
	Button* backButton;
	Button* newButton;
	Button* oldButton;
	Button* playStopButton;
	FieldControl* field;

	bool selectTextureWindow;
	
	link<Animation>& anim;
	int id;
	int data_from_window;
	float i_time;
	int i_frameCount;
	bool isPlaying;

public:
	NewAnim(GameObjectManager* gom, link<Animation>* anim);
	void Draw();
	void Update(double deltaTime);
};


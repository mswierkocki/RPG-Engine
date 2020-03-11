#pragma once
#include "window.h"
#include "GameObjectManager.h"
#include "Engine.h"
#include "TextureControl.h"
#include "Button.h"
#include "SelectControl.h"
#include "LabelControl.h"
#include "FieldControl.h"

class ObjectManagerWindow :public Window
{
private:
	GameObjectManager* gom;
	Engine* engine;

	Button* o_delButton;
	Button* o_addButton;
	Button* o_importButton;
	Button* o_editButton;
	Button* o_searchButton;
	Button* o_backButton;
	Button* o_minMaxButton;
	TextControl* o_filtr;
	SelectControl* o_select;

	link<Object> o_object;
	int o_objectId;
	bool o_editWindow;
	bool minim;

	bool change;

	float lx,ly;

	bool drag;

public:
	ObjectManagerWindow(GameObjectManager* gom, Engine* engine);

	void Draw();

	void Update(double deltaTime);

	void SetVisible();

	void SetInVisible();

	void SwitchVisible();

	bool IndexChange();

	int GetSelectedIndex();
};


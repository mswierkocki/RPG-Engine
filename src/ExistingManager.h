#pragma once
#include "window.h"
#include "GameObjectManager.h"
#include "Engine.h"
#include "TextureControl.h"
#include "Button.h"
#include "SelectControl.h"
#include "LabelControl.h"
#include "FieldControl.h"
#include "MultiSelectControl.h"

class ExistingManager :public Window
{
private:
	GameObjectManager* gom;
	Engine* engine;
	vector<int>& selected;

	Button* delButton;
	Button* editButton;
	Button* searchButton;
	Button* backButton;
	Button* minMaxButton;
	Button* allNoneButton;
	Button* goToButton;
	TextControl* filtr;
	MultiSelectControl* multiselect;

	link<Object> object;
	int objectId;
	bool editWindow;

	bool change;
	bool minim;

	float lx,ly;

	bool drag;

public:
	ExistingManager(GameObjectManager* gom, Engine* engine, vector<int>* selected);

	void Draw();

	void Update(double deltaTime);

	void SetVisible();

	void SetInVisible();

	void SwitchVisible();

	bool IndexChange();

	int GetSelectedIndex();

	void ForceSelect(int s, bool b);

	void ClearSelection();
};



#pragma once
#include "window.h"
#include "Texture.h"
#include "Object.h"
#include "Button.h"
#include "TextControl.h"
#include "FieldControl.h"
#include "SelectControl.h"
#include "GameObjectManager.h"
#include "Engine.h"

class ObjectWindow :public Window
{
private:
	GameObjectManager* gom;
	Engine* engine;

	Button* addAnim;
	Button* delAnim;
	Button* editAnim;
	Button* startPoli;
	Button* stopPoli;
	Button* startPoli2;
	Button* stopPoli2;
	Button* playAnim;
	Button* okButton;
	Button* backButton;
	TextControl* name;
	TextControl* tag;
	TextControl* scriptBox;
	TextControl* classBox;
	FieldControl* field;
	SelectControl* select;

	bool drawCollisio;
	bool drawOcllusion;

	bool creatingCollisio;
	bool creatingOcllusion;

	Poly* polygon;  

	link<Object>& object;
	link<Animation> anim;
	link<Animation> current;

	bool newAnimWindow;
	bool editAnimWindow;
	bool isPlaying;
	bool czyEdycja; 

	int animNr;
	vector<link<Animation>> animations;

	bool drag;
	float lx,ly;

public:
	ObjectWindow(GameObjectManager* gom, Engine* engine, link<Object>* object);

	void Draw();
	void Update(double deltaTime);
};


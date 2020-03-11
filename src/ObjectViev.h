#pragma once
#include "window.h"
#include "Object.h"
#include "Button.h"
#include "TextControl.h"
#include "LabelControl.h"
#include "FieldControl.h"

class ObjectView :public Window
{
private:
	link<Object> object;
	link<Animation> current;

	Button* lButton;
	Button* rButton;
	Button* playButton;
	TextControl* nr;
	LabelControl* title;
	LabelControl* name;
	LabelControl* tag;
	FieldControl* field;
	TextControl* scaleBox;


	bool isPlaying;
	int animNr;

	bool drag;
	float lx,ly;

public:
	ObjectView(void);

	void SetObject(link<Object> o);
	void SetTitle(string s);
	
	void Draw();
	void Update(double deltaTime);

	void SetVisible();
	void SetInVisible();
	void SwitchVisible();
};


#pragma once
#include "window.h"
#include "Button.h"
#include "TextControl.h"
#include "TextureControl.h"
#include "LabelControl.h"
#include "Event.h"

class AskWindow :public Window
{
private:
	Button* okButton;
	Button* backButton;
	TextControl* answer;
	TextureControl* bg;
	LabelControl* info;

	string* ans;

public:
	AskWindow(string text, string* ans);

	void Draw();
	void Update(double deltaTime);
};


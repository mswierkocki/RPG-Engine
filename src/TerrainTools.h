#pragma once
#include "window.h"
#include "Button.h"
#include "FieldControl.h"
#include "Engine.h"

class TerrainTools :public Window
{
private:
	Engine* engine;

	Button* backButton;
	Button* lButton;
	Button* rButton;
	Button* brushButton;
	Button* eraseButton;
	Button* baseButton;
	Button* cutButton;
	Button* x1Button;
	Button* x2Button;
	Button* x3Button;
	FieldControl* field;

	int base;

	bool isBase;
	bool isBrush;
	bool isErase;
	bool isCut;

	int maxBase;
	int maxRandom;
	int size;

public:
	TerrainTools(Engine* engine);

	void Draw();
	void Update(double deltaTime);

	void SetVisible();
	void SetInVisible();
	void SwitchVisible();

	void Set(unsigned int x, unsigned int y);
};


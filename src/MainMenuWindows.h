#pragma once
#include "Window.h"
#include "Event.h"
#include "Button.h"

class MainMenuWindows :public Window
{
private:
	Button* newGameButton;
	Button* exitGameButton;
	Button* edytorButton;

public:
	MainMenuWindows(void);

	void Update(double deltaTime);
	void Draw();
};


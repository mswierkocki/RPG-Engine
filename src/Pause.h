#pragma once
#include "window.h"
#include "Button.h"

class Pause : public Window
{
private:
	Button* loadButton;
	Button* escButton;
	Button* backButton;

public:
	Pause(void);

	void Draw();
	void Update(double deltaTime);
};


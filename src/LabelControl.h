#pragma once
#include "Controlka.h"
#include <string>

using namespace std;

class LabelControl: public Controlka
{
private:
	string text;
	Color3f color;

public:
	LabelControl(Window* parent,string text, Color3f color, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(), float scale = 1);
	void SetText(string s) {text = s;}
	void Draw();
	void Update();
};


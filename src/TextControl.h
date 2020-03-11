#pragma once
#include "Controlka.h"
#include "Texture.h"
#include <string>
#include <vector>
using namespace std;

class TextControl: public Controlka
{
private:
	string text;        // text w boxie
	bool enable;
	bool enter;
	float width;        // szerokosc kontrolki,

	static Texture* bg;

public:
	TextControl(Window* parent, float width, bool enable = true, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(), float scale = 1.0f);

	void SetText(string t) {text = t;}
	string GetText() {return text;}

	void SetEnable(bool b) {enable = b;}

	bool Enter() {if(enter) {return !(enter = false);} else return false;}

	void Draw();
	void Update();
	static void Init()
	{
		bg = new Texture("Edytor\\txtbar.png");
	}
};


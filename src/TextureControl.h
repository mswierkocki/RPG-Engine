#pragma once
#include "controlka.h"
#include "Texture.h"

class TextureControl :public Controlka
{
private:
	Texture* texture;
	float w,h;

public:
	TextureControl(Window* parent, std::string file, float w, float h, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf());

	void Draw();
	void Update();
	void SetHeight(float h) { this->h = h;}
	void SetWidth(float w) {this->w = w;}
};



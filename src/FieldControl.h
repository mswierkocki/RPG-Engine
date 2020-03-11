#pragma once
#include "controlka.h"
class FieldControl :public Controlka
{
private:
	float w,h;

public:
	FieldControl(Window* parent,float h, float w, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf());

	void CountField(float texw, float texh, Pointf& off, Pointf& size);

	void Draw();
	void Update();

};


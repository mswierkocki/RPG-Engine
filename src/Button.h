#pragma once

#include "Controlka.h"



class Button: public Controlka
{
protected:
	int status; //0 - NIC // 1 - POKRYTY // 2 - NACISNIETY

public:
	bool pressed;

	Button(Window* parent,float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(),float scale = 1)
		:Controlka(parent,dockx,docky,OffsetPX, OffsetPC,scale),pressed(false) {}

	virtual void Draw() = 0;
	virtual void Update() = 0;

	void ForceState(int s) {status = s;}
};

class ImgButton: public Button
{
private:
	Texture* image;

public:
	ImgButton(Window* parent, std::string fileName, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(),float scale = 1)
		:Button(parent,dockx,docky,OffsetPX,OffsetPC,scale)
	{
		image = new Texture(fileName);
	}

	void Draw();
	void Update();
};

class TextButton: public Button
{
private:
	std::string text;
	float width;
	static Texture* bg;

public:
	TextButton(Window* parent, std::string text, float width = 0, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(),float scale = 1)
		:Button(parent,dockx,docky,OffsetPX,OffsetPC,scale),text(text),width(width)
	{
	}

	void Draw();
	void Update();
};

class MixedButton: public Button
{
private:
	std::string text;
	float width;
	Texture* image;

public:
	MixedButton(Window* parent, std::string fileName, std::string text, float width = 0, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(),float scale = 1)
		:Button(parent,dockx,docky,OffsetPX,OffsetPC,scale),text(text),width(width)
	{
		image = new Texture(fileName);
	}

	void Draw();
	void Update();
};

class ImgHintButton: public Button
{
private:
	Texture* image;
	string hint;

public:
	ImgHintButton(Window* parent, std::string fileName, std::string hint, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(),float scale = 1)
		:Button(parent,dockx,docky,OffsetPX,OffsetPC,scale),hint(hint)
	{
		image = new Texture(fileName);
	}

	void Draw();
	void Update();
};
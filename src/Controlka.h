#pragma once
#include "utils.h"
#include "Texture.h"

class Window;

typedef struct _GLYPHMETRICSFLOAT GLYPHMETRICSFLOAT;

class Controlka
{
protected:
	Window* parent;   //okieno przycisku

	Pointf offsetPX;  //offset w pixelach
	Pointf offsetPC;  //offset w procetach
	float dockX, dockY; // 0,0 - leftDown | 1,1 center
	float scale;      //skala bitmapy
	
	
	static Texture* font; 
	static unsigned int	base;				// Base Display List For The Font Set
	static GLYPHMETRICSFLOAT gmf[256];	// Storage For Information About Our Outline Font Characters

public:
	bool visible;

	Controlka(Window* parent,float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(),float scale = 1)
		:dockX(dockx),dockY(docky),parent(parent),offsetPX(OffsetPX),offsetPC(OffsetPC),scale(scale),visible(true) {}

	virtual void Draw() = 0;
	virtual void Update() = 0;

	static void BuildFont();
	
	void glPrint(float x, float y, const char *fmt, ...);

	static void glPrint(float x, float y, float scale, const char *fmt, ...);

	float GetTextLength(const char* text);
	//float GetFontHeight() {return 


	static void Init()
	{
		BuildFont();
		//font = new Texture("Inne\\font.tga");
	}
};


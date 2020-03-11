#pragma once

#include "link.hpp"

#include <vector>
#include "Texture.h"
#include "Object.h"

struct Kafelek
{
public:
	char base, baseNr, type, nr, typeNr;
	Kafelek(char base = 0, char type = 0, char nr = 0):base(base),type(type),nr(nr){}
	void SetBase(char b, char max) {base = b; baseNr = rand() % max;}
	void SetType(char b, char max) {type = b; typeNr = rand() % max;}
	float operator[](int i) {return (i == 0) ? type : nr;}
};

#define TILESIZE 128

class Map
{
private:
	std::vector<std::link<Object>> objects;
	Kafelek* tab;
	int w;
	int h;

	static Texture* parts;
	static Texture* base;

public:
	Map(){}
	Map(int w, int h):w(w),h(h) { tab = new Kafelek[w*h]; }
	Map(int w, int h, char base);

	int GetW() { return w*TILESIZE; }
	int GetH() { return h*TILESIZE; }
	unsigned GetWidth() { return w; }
	unsigned GetHeight() { return h; }

	Kafelek* GetKafelkiPtr() { return tab; }
	void SetKafelkiPtr(Kafelek* ptr) { tab = ptr; }

	Kafelek& Get(int x, int y);
	void Refresh(int x, int y);

	static Texture* GetParts() { return parts; }
	static Texture* GetBase() { return base; }

	static void Init()
	{
		parts = new Texture("Edytor\\parts.png");
		base = new Texture("Edytor\\base.png");
		glBindTexture(GL_TEXTURE_2D,base->texID);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D,parts->texID);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	}

	static int GetBaseCount() { return base->width/TILESIZE; }
	static int GetBaseRandom() { return base->height/TILESIZE; }

	std::vector<std::link<Object>>& GetObjectVecRef() { return objects; }
};

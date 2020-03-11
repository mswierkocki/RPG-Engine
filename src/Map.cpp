#include "Map.h"


Map::Map(int w, int h, char base):w(w),h(h)
{
	tab = new Kafelek[w*h];
	int r = GetBaseRandom();
	for(int i=0; i<w*h; i++)
	{
		tab[i].type = 124;
		tab[i].nr = 0;
		tab[i].base = base;
		tab[i].baseNr = (rand() % r);
	}
}

Kafelek& Map::Get(int x, int y)
{
	return tab[x+w*y];
}


void Map::Refresh(int x, int y)
{
	int c0 = (Get(x-1,y+1).type == Get(x,y).type)?1:0;
	int c1 = (Get(x,y+1).type == Get(x,y).type)?1:0;
	int c2 = (Get(x+1,y+1).type == Get(x,y).type)?1:0;

	int c5 = (Get(x,y-1).type == Get(x,y).type)?1:0;
	int c6 = (Get(x-1,y-1).type == Get(x,y).type)?1:0;
	int c7 = (Get(x-1,y).type == Get(x,y).type)?1:0;

	int sum4 = c1 + c3 + c5 + c7;

	int sum = c0 + c1 + c2 + c3 + c4 + c5 + c6 + c7;

	if(sum4 == 0)
	{
		Get(x,y).nr = 0;
	}
	if(sum4 == 1)
	{
		if(c1) Get(x,y).nr = 3;
		if(c3) Get(x,y).nr = 4;
		if(c5) Get(x,y).nr = 1;
		if(c7) Get(x,y).nr = 2;
	}
	if(sum4 == 2)
	{
		if(c5 && c3) Get(x,y).nr = (c4)?12:8;
		if(c1 && c3) Get(x,y).nr = (c2)?11:7; 

		if(c5 && c1) Get(x,y).nr = 17;
		if(c7 && c3) Get(x,y).nr = 18;
	}
	if(sum4 == 3)
	{
		if(c7 && c3 && c5) Get(x,y).nr = (c6)?((c4)?27:19):((c4)?23:13);
		if(c1 && c3 && c5) Get(x,y).nr = (c4)?((c2)?30:22):((c2)?26:16);
		if(c7 && c1 && c5) Get(x,y).nr = (c0)?((c6)?28:20):((c6)?24:14);
	}
	if(sum4 == 4)
	{
		int sum44 = c0 + c2 + c4 + c6;
		
		if(sum44 == 0)
		{
			Get(x,y).nr = 32;
		}
		if(sum44 == 1)
		{
			Get(x,y).nr = (c2)?34:((c0)?33:((c6)?36:35));
		}
		if(sum44 == 2)
		{
			if(c2 && c4) Get(x,y).nr = 39; 
			if(c2 && c0) Get(x,y).nr = 38;
			if(c6 && c4) Get(x,y).nr = 40;
			if(c0 && c4) Get(x,y).nr = 42;
			if(c2 && c6) Get(x,y).nr = 41;
		}
		if(sum44 == 3)
		{
			Get(x,y).nr = (!c2)?44:((!c0)?43:((!c6)?46:45));
		}
		if(sum44 == 4)
		{
			Get(x,y).nr = 31;
		}
	}
}

////////////////////////////////
Texture* Map::parts;
Texture* Map::base;
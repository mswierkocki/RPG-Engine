#pragma once
#include "Controlka.h"
#include <string>
#include <vector>

using namespace std;

class SelectControl :public Controlka
{
private:
	int max;
	int selected;
	int pos;
	bool change;
	float width;
	float lw;

	vector<string> list;

public:
	SelectControl(Window* parent,int max, float width, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(), float scale = 1);

	void Draw();
	void Update();
	//void WriteText(float x, float y, string text, float height);
	void SetList(vector<string>& s) 
	{
		list = s;
		//for(unsigned int i = 0; i<list.size(); i++)
		//{
		//	char buff[10];
		//	list[i] = string(_itoa((i-pos+1),buff,10)) + "." + list[i];
		//}
	}
	int GetSelectedIndex() {return selected;}
	//Very dengerous
	void ForceSelect(int s);
	bool IndexChange() {if(change) {change = false; return true;} else return false;}
};


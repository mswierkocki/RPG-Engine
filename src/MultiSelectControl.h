#pragma once
#include "Controlka.h"
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class MultiSelectControl :public Controlka
{
private:
	int max;
	vector<bool> selected;
	int pos;
	int lastSelected;
	int count;
	int action;
	bool change;
	float width;
	float lw;

	vector<string> list;

public:
	MultiSelectControl(Window* parent,int max, float width, float dockx = 0, float docky = 0, Pointf OffsetPX = Pointf(), Pointf OffsetPC = Pointf(), float scale = 1);

	void Draw();
	void Update();
	void SetList(vector<string>& s);
	int GetSelectedIndex() {return lastSelected;}
	int GetSelectedCount() {return count;}
	int GetSelectedType() {return action;}
	//Very dengerous
	bool ForceSelect(int s, bool b);
	void ClearSelection() {for(unsigned i = 0; i < selected.size(); i++) selected[i] = false; count = 0; }
	bool IndexChange() {if(change) {change = false; return true;} else return false;}
};




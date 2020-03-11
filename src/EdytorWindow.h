#pragma once
#include "window.h"
#include "Engine.h"
#include "GameObjectManager.h"
#include "TextureControl.h"
#include "Button.h"
#include "SelectControl.h"
#include "LabelControl.h"
#include "FieldControl.h"
#include "ObjectManagerWindow.h"
#include "ObjectViev.h"
#include "ExistingManager.h"
#include "TerrainTools.h"

class EdytorWindow :public Window
{
private:
	GameObjectManager* gom;
	Engine* engine;
	vector<int> selected;
	vector<int> storage;
	link<Object> newObject;
	link<Map> newMap;
	bool drag,mpress,grab;
	bool editWindow;
	bool saveAsWindow;
	string nameFromAsk;

	bool newMapWindow;
	bool oldMapWindow;
	bool saveForNew;
	bool saveForOld;

	bool saveResult;
	int mapId;

	Button* newMapButton;
	Button* oldMapButton;
	Button* saveButton;
	Button* saveAsButton;
	Button* objectManagerButton;
	Button* viewButton;
	Button* properties;
	Button* scriptEditor;
	Button* mapSettings;
	Button* objectListButton;
	Button* zoomInButton;
	Button* zoomOutButton;
	Button* zoom100Button;
	Button* playButton;
	Button* stopButton;
	Button* texturesButton;
	Button* terrainButton;
	Button* gridButton;
	Button* resetButton;

	bool isPlaying;
	bool gridVisible;

	float lx,ly;
	int lw;

	unsigned int kolejnosc;

	/////////////OKNA/////////
	ObjectManagerWindow* manager;
	ExistingManager* existing;
	ObjectView* view;
	TerrainTools* terrain;

	Texture* bar;
	Texture* bar2;




public:
	EdytorWindow(Engine* e,GameObjectManager* gom);

	void Draw();
	void Update(double deltaTime);
};


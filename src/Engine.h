#pragma once
#include "utils.h"
#include "GameObjectManager.h"
#include "Map.h"
#include "Screen.h"

class Engine
{
private:
	GameObjectManager *gom;
	std::link<Map> currentMap;
	float zoom;
	int state;
	Pointf mapCoords; 
	bool framesEnabled;
	bool polygonsEnabled;

public:
	Engine(GameObjectManager *gom);
	void Draw();
	void DrawMap();
	void DrawGrid();
	void DrawObjects();
	void DrawObject(Object* o);
	void DrawFrame(Object* o);
	void DrawPolygon(Object* o);
	void MoveMap(Pointf mov);
	void SetMapPos(Pointf mov);
	void Zoom(int z);
	void ResetZoom() { state = 6; Zoom(0); }
	Pointf GetMapCoords() {return mapCoords; }
	float GetZoom() { return zoom; }
	vector<link<Object>*> GetObjectsUnderMouse();
	vector<int> GetObjectsIdUnderMouse();
	std::link<Map>& GetCurrentMap() { return currentMap; }
	void SetCurrentMap(const std::link<Map>& map) { currentMap = map; }
	void SetCurrentMap(int id) {currentMap = gom->GetMapByID(id);}
	bool HasMap() {return (currentMap._Ptr == nullptr)?false:true;}
	void SetFramesMode(bool b) { framesEnabled = b; }
	void SetPolygonsMode(bool b) { polygonsEnabled = b; }
	void Save();
	void Update(double deltaTime);
};


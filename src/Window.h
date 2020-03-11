#pragma once
#include <vector>
#include "Screen.h"
#include "utils.h"
#include "Texture.h"
#include "Controlka.h"
#include "TextControl.h"
#include "Button.h"
#include "link.hpp"

enum WINDOWS_TYPE {MAIN_MENU_WINDOWS = 0, LOAD_GAME_WINDOWS, GAME_WORLD_WINDOWS, INTERFACE_WINDOWS, PAUSE_WINDOWS,
	               EDYTOR_WINDOWS, OBJECT_WINDOWS, NEW_ANIM_WINDOWS, SELECT_TEXTURE_WINDOW, NEW_TEXTURE_WINDOW, 
				   OLD_TEXTURE_WINDOW, SELECT_MAP_WINDOW, NEW_MAP_WINDOW, OLD_MAP_WINDOW, OLD_OBJECT_WINDOW,
				   ASK_WINDOW, SAVE_WINDOW, WINDOWS_COUNT}; 


class Window
{
private:
	static Texture* font;

protected:
	bool active;
	bool visible;
	float dockX,dockY;
	Pointf offsetPX,offsetPC;
	float w,h;
	WINDOWS_TYPE type;
	vector<Controlka*> controls;

public:
	Controlka* focus;

	virtual void Update(double deltaTime) = 0;
	virtual void Draw() = 0;

	inline Pointf getOffset() 
	{
		float W = screen->getWidth(), H = screen->getHeight();
		return Pointf((dockX * (W - w)) / 2.0f + offsetPX[0] + offsetPC[0] * W,
					  (dockY * (H - h)) / 2.0f + offsetPX[1] + offsetPC[1] * H);
	}
	float getWidth() {return w;}
	float getHeight() {return h;}

	Window(float w = screen->getWidth(), float h = screen->getHeight(), float dockx = 0, float docky = 0, Pointf offsetPX = Pointf(0,0),
		   Pointf offsetPC = Pointf(0,0)):w(w),h(h),offsetPX(offsetPX),offsetPC(offsetPC),dockX(dockx),dockY(docky),focus(nullptr) {}

	bool isActive() {return active;}
	bool isVisible() {return visible;}
	void switchActive() {active = !active;} //Zmienia flage aktywnosci na przeciwna
	void switchVisible() {visible = !visible;} // Zmienia flage widocznosci na przeciwna
	void setActive() {active = true;} // Ustawia flage okna na Aktywne
	void setVisible() {visible = true;} // Ustawia flage okna na Widoczne
	void setInActive() {active = false;} // Ustawia flage okna na Nie aktywne
	void setInVisible() {visible = false;} // Ustawia flage okna na Nie widoczne
	WINDOWS_TYPE getType(){return type;}

	static void Init() {font = new Texture("Inne\\font.tga");}
	
	void LoadContent(string file, vector<link<Controlka*>>& tmp = vector<link<Controlka*>>());
};

/*  Okienka sa bardzo przyjemne.
	Dodajemy nowe okienko dziedziczace po clasie Window.
	Nalezy w nim zadeklarowac funkcje Draw() i Update(double deltaTime);
	Nastepnie dodajemy do enuma WINDOWS_TYPE nowy rodzaj okienka
	Nastepnie nalezalo by w gameManagerze dodac opcje dodania nowego okienka naszego typu.
	
	*/

extern std::vector<Window*> windowsQueue;
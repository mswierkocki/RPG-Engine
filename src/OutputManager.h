#pragma once

#include"Screen.h"



class OutputManager
{
private:
	
	int ScreenWidth;
	int ScreenHeight;
	

public:
	void Run(double deltaTime);
	void ClearScene() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();}
	void CreateScene();
	Screen* GetScreen(){return screen;}
	void setSize(Dimension d){ ScreenWidth = d.x; ScreenHeight=d.y; } // ustawia wymiary screenu (D.Szerokosc,D.Wysokosc)
	void setSize(int x, int y){ ScreenWidth = x;  ScreenHeight= y;} // ustawia wymiary screenu (Szerokosc,Wysokosc)
	void setHeight(int h){ScreenHeight= h;} // ustawia wysokosc screenu
	void setWidth(int w){ScreenWidth = w;} // Ustawia szerokosc screenu
};

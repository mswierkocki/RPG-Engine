#pragma once

#include "utils.h"
#include "InputManager.h"
#include <cstdlib>
#include <string>
using namespace std;



struct Dimension{
	Dimension():x(0),y(0){}
	Dimension(int a,int b):x(a),y(b){}
	int x,y;
};
class Screen
{
private:
	int Width;
	int Height;
public:

	Screen(int width, int height);
	static void GLFWCALL ReSizeGLScene(int w, int h);

	void run(double deltaTime);
	void setWidth(int w){Width = w;}
	void setHeight(int h){Height = h;}
	int getWidth(){return Width;}
	int getHeight(){return Height;}
	void setSize(Dimension d){ Width = d.x; Height=d.y; } // ustawia wymiary screenu (D.Szerokosc,D.Wysokosc)
	
};
extern Screen* screen;
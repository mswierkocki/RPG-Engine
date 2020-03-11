#pragma once

#include <Windows.h>
#define GLFW_DLL
#include "GL/glfw.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include "Geometry.h"
using namespace std;


struct Color3f
{
	float r,g,b;
	Color3f(float r = 0, float g = 0, float b = 0):r(r),g(g),b(b) {}
	Color3f(char* s){
		r = atof(strtok(s," ,"))/255.0f;
		g = atof(strtok(NULL," ,"))/255.0f;
		b = atof(strtok(NULL," ,"))/255.0f;
	}
	void Colorize() {glColor3f(r,g,b);} 
};


namespace Timer
{
	void Start();
	void Stop();
	double GetTime();
}

namespace Input
{
	typedef struct Bind 
	{
		std::string name;
		//std::string reference;
		char z;
		//char alt;
		Bind(std::string n, char c=0):name(n),z(c){}
	}Bind;

	enum State {KEY_UP,KEY_DOWN, KEY_PRESS}; //TODO
	enum Buttons {B_LEFT, B_RIGHT, B_MIDDLE};

	bool isPressed(Bind* wz);
	bool isDown(Bind * wz, bool b = false);
	bool isPressed(int k);
	bool isDown(int k, bool b = false);
	int GetY();
	int GetX();
	int GetChar();
	void ClearChar();
	int GetKey();
	void ClearKey();
	State GetButtState(int a);
	bool GetButtPressed(int a);

	namespace IK
	{
		#define SPACEBAR GLFW_KEY_SPACE
		#define ESC GLFW_KEY_ESC
		#define DOWN GLFW_KEY_DOWN
		#define LEFT GLFW_KEY_LEFT
		#define UP GLFW_KEY_UP
		#define RIGHT GLFW_KEY_RIGHT
	}

namespace InputManager{
/////////////////////////////////////////////////////////////
	
	extern State keys[GLFW_KEY_LAST];
	extern State butt[3];
	extern int x,y;

	extern bool consumed;
	extern int s_x,s_y;
	extern State s_b1, s_b2, s_b3;

	void Consume();
	inline void ConsumeMouse() 
	{
		consumed = true;
	}
	inline void RestoreMouse()
	{
		consumed = false;
	}
	inline State GetState(int k) {return keys[k];}
	inline void SetState(State s, int k) { keys[k] = s;}
	void GLFWCALL KeyCallback(int key, int action);
	void GLFWCALL MouseCallback(int x, int y);
	void GLFWCALL MouseButtonCallback(int button, int action);
	void GLFWCALL CharCallback(int character, int action);

}

/*
**** Dodanie nowego bind-a!!!
W utils.h musi mieæ extern
extern Bind* toggleSkillsMenu;
Musi byæ dodatkowo stworzony w pliku utils.cpp (Du¿e litery!)
Bind* toggleSkillsMenu = new Bind("ToggleSkillsMenu",'Z');
Lub
Bind* toggleSkillsMenu = new Bind("ToggleSkillsMenu");
Nie zapomnij go dodaæ do wczytywaniu z configa!!
GameManager.cpp
if(!cfg.getValue("Keys",Input::toggleSkillsMenu->name,&Input::toggleSkillsMenu->z))
  Input::toggleSkillsMenu->z = 'C';
i
  cfg.addEntry("Keys",Input::toggleSkillsMenu->name,"P");
*/
extern Bind* toggleSkillsMenu;
extern Bind* MoveUp;
extern Bind* MoveDown;
extern Bind* MoveRight;
extern Bind* MoveLeft;
}

template <class T>
string etos(T t)
{
	stringstream ss;
	ss << (int)(t * 100) / 100.0f;
	return ss.str();
}
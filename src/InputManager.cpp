#define GLFW_DLL

#include "InputManager.h"
#include <iostream>
void GLFWCALL InputManager::KeyCallback(int key, int action)
{

	if(action == GLFW_RELEASE)
		{
			if(keys[key] == KEY_DOWN) keys[key] = KEY_PRESS;
			else if(keys[key] == KEY_PRESS) keys[key] = KEY_UP;
		}
	else if(action == GLFW_PRESS)
		{
			keys[key] = KEY_DOWN;
		}
		
//	std::cout<<"Klawisz "<<(char)key<<" code "<<key<<"Nasz status "<<keys[key]<<std::endl;
}

void GLFWCALL InputManager::MouseCallback(int xx, int yy)
{
	x = xx;
	y = yy;
}

void GLFWCALL InputManager::MouseButtonCallback(int button, int action)
{
	switch(button)
	{
	case GLFW_MOUSE_BUTTON_LEFT: 
		if(action == GLFW_RELEASE)
		{
			if(butt[B_LEFT] == KEY_DOWN) butt[B_LEFT] = KEY_PRESS;
			else if(keys[B_LEFT] == KEY_PRESS) butt[B_LEFT] = KEY_UP;
		}
		else if(action == GLFW_PRESS)
		{
			butt[B_LEFT] = KEY_DOWN;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT: 
		if(action == GLFW_RELEASE)
		{
			if(butt[B_RIGHT] == KEY_DOWN) butt[B_RIGHT] = KEY_PRESS;
			else if(keys[B_RIGHT] == KEY_PRESS) butt[B_RIGHT] = KEY_UP;
		}
		else if(action == GLFW_PRESS)
		{
			butt[B_RIGHT] = KEY_DOWN;
		}
		break;
	}
}

void InputManager::mapToKey(GameEvent *ev, int keyCode)
{
	gameEvents[keyCode].push_back(ev);
}
///////////////////
State InputManager::keys[GLFW_KEY_LAST] = {};
State InputManager::butt[3] = {KEY_UP,KEY_UP,KEY_UP};
int InputManager::x = 0;
int InputManager::y = 0;
vector<GameEvent*> InputManager::gameEvents[GLFW_KEY_LAST] = {};


#include "utils.h"
#include "Lindows.h"

namespace Input{
///////////////////Bindy//////////////////////////////
Bind* toggleSkillsMenu	= new Bind("ToggleSkillsMenu");
Bind* MoveUp			= new Bind("MoveUp");
Bind* MoveDown			= new Bind("MoveDown");
Bind* MoveRight			= new Bind("MoveRight");
Bind* MoveLeft			= new Bind("MoveLeft");
/////////////////////////////////////////////////////
namespace InputManager{

	State keys[GLFW_KEY_LAST];
	State butt[3];
	int x,y;
	int lastChar;
	int lastKey;
	
	int s_x,s_y;
	State s_b1, s_b2, s_b3;
	bool consumed;
	bool pressed[3];

	///////////////////////////////////////////////////////////
	void GLFWCALL  KeyCallback(int key, int action)
	{

		if(action == GLFW_RELEASE)
			{
				if(keys[key] == KEY_DOWN) keys[key] = KEY_PRESS;
				else if(keys[key] == KEY_PRESS) keys[key] = KEY_UP;
			}
		else if(action == GLFW_PRESS)
			{
				keys[key] = KEY_DOWN;
				lastKey = key;
			}

	}

	void GLFWCALL  MouseCallback(int xx, int yy)
	{
		x = xx;
		y = yy;
	}

	void GLFWCALL  MouseButtonCallback(int button, int action)
	{
		switch(button)
		{
		case GLFW_MOUSE_BUTTON_LEFT: 
			if(action == GLFW_RELEASE)
			{
				butt[B_LEFT] = KEY_PRESS;
			}
			else if(action == GLFW_PRESS)
			{
				butt[B_LEFT] = KEY_DOWN;
				pressed[B_LEFT] = true;
			}
			break;
		case GLFW_MOUSE_BUTTON_RIGHT: 
			if(action == GLFW_RELEASE)
			{
				butt[B_RIGHT] = KEY_PRESS;
			}
			else if(action == GLFW_PRESS)
			{
				butt[B_RIGHT] = KEY_DOWN;
				pressed[B_RIGHT] = true;
			}
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE: 
			if(action == GLFW_RELEASE)
			{
				butt[B_MIDDLE] = KEY_PRESS;
			}
			else if(action == GLFW_PRESS)
			{
				butt[B_MIDDLE] = KEY_DOWN;
				pressed[B_MIDDLE] = true;
			}
			break;
		}
	}

	void GLFWCALL CharCallback(int character, int action)
	{
		if(action == GLFW_PRESS)
			lastChar = character;
	}


	void Consume(){
		for (unsigned int i = 0; i<GLFW_KEY_LAST;i++){
			keys[i] = KEY_UP;
		}
	}
////////////////////Koniec InputManagera /////////////////////////////
}

State GetButtState(int a) {return (InputManager::consumed)?KEY_UP:InputManager::butt[a];}
bool GetButtPressed(int a) { if(InputManager::pressed[a]) {InputManager::pressed[a] = false; return true;} else return false; }

int GetX() {return (InputManager::consumed)?0:InputManager::x;}

int GetY() {return (InputManager::consumed)?0:InputManager::y;}

void ClearChar() { InputManager::lastChar = 0;}

void ClearKey() { InputManager::lastKey= 0;}

int GetChar() {return InputManager::lastChar;}

int GetKey() {return InputManager::lastKey;}

bool isDown(Bind * wz, bool b){
	if(wz == nullptr) return false;
	if( InputManager::GetState(wz->z) == State::KEY_DOWN){
		if (b) InputManager::SetState(KEY_UP,wz->z);
		return true;
	}		
		return false;
}

bool isPressed(Bind* wz){
	if(wz == nullptr) return false;
	if( InputManager::GetState(wz->z) == State::KEY_PRESS){
		InputManager::SetState(KEY_UP,wz->z);
		return true;
	}		
		return false;
}

bool isPressed(int k)
{                                     
	if( InputManager::GetState(k) == State::KEY_PRESS){
		InputManager::SetState(KEY_UP,k);
		return true;
	}		
		return false;
}
bool isDown(int k, bool b)
{
	if( InputManager::GetState(k) == State::KEY_DOWN){
		if (b) InputManager::SetState(KEY_UP,k);
		return true;
	}		
		return false;
}

////////////////////Koniec Inputa /////////////////////////////
}

namespace Timer
{
	static time_t clock,start,stop;
	void Start() { QueryPerformanceFrequency((LARGE_INTEGER*)&clock); QueryPerformanceCounter((LARGE_INTEGER*)&start); }
	void Stop() { QueryPerformanceCounter((LARGE_INTEGER*)&stop); }
	double GetTime() { return double(stop-start)/clock; }
}

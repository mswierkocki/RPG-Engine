#pragma once

#include <string>
#include <vector>
using namespace std;

class GameEvent
{
	//enum STATE{NORMAL,ACTION};
	//int state;
	//std::string name; 
	//
	//GameEvent(std::string name):name(name),state(NORMAL){}
	//~GameEvent(void);
	//void reset(){state = NORMAL;}
	//bool isAction(){return state ==ACTION;}
	//void action(){state = ACTION;}
public:
	static vector<GameEvent*> eventQueue;
	typedef void (*EventFunc)(void*);

	GameEvent(void* s, EventFunc e):sender(s),eventFunc(e),active(true) {}

public:
	bool active; //execution check
	void* sender; //sender
	EventFunc eventFunc; //action
};

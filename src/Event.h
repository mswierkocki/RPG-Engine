#pragma once
#include <vector>
#include "Window.h"
using namespace std;

class Event
{
public:
	int Id;

	Event(int id):Id(id) {}
};

enum EVENT_TYPE { EXIT_EVENT = 0, KILL_LAST_EVENT, KILL_WINDOW_EVENT, NEW_WINDOW_EVENT, SET_VISIBLE_EVENT, SET_ACTIVE_EVENT,
				  SET_ALL_VISIBLE_EVENT, SET_ALL_ACTIVE_EVENT, SET_LAST_ACTIVE_EVENT};
enum BOOL_TYPE { SET_FALSE = 0, SET_TRUE, SET_OPPOSITE };

extern vector<Event*> eventQueue;

class ExitEvent: public Event
{
public:
	ExitEvent():Event(0) {}
};

class KillLastEvent: public Event
{
public:
	KillLastEvent():Event(1) {}
};

class KillWindowEvent: public Event
{
public:
	int windowType;

	KillWindowEvent(WINDOWS_TYPE id):windowType(id),Event(KILL_WINDOW_EVENT) {}
};

class NewWindowEvent: public Event
{
public:
	int windowType;
	vector<void*>* params;

	NewWindowEvent(WINDOWS_TYPE id,vector<void*>* p = nullptr):windowType(id),params(p),Event(NEW_WINDOW_EVENT) {}
};

class SetVisibleEvent: public Event
{
public:
	int windowType;
	int setOption;

	SetVisibleEvent(WINDOWS_TYPE id, BOOL_TYPE option):windowType(id),setOption(option),Event(SET_VISIBLE_EVENT) {}
};

class SetActiveEvent: public Event
{
public:
	int windowType;
	int setOption;

	SetActiveEvent(WINDOWS_TYPE id, BOOL_TYPE option):windowType(id),setOption(option),Event(SET_ACTIVE_EVENT) {}
};

class SetAllVisibleEvent: public Event
{
public:
	int setOption;

	SetAllVisibleEvent(BOOL_TYPE option):setOption(option),Event(SET_ALL_VISIBLE_EVENT) {}
};

class SetAllActiveEvent: public Event
{
public:
	int setOption;

	SetAllActiveEvent(BOOL_TYPE option):setOption(option),Event(SET_ALL_ACTIVE_EVENT) {}
};

class SetLastActiveEvent: public Event
{
public:
	int setOption;

	SetLastActiveEvent(BOOL_TYPE option):setOption(option),Event(SET_LAST_ACTIVE_EVENT) {}
};

#include "Lindows.h"

#include "GameManager.h"

#include "Py/Python.h"

using namespace std;

int main()
{
	Py_Initialize();
	PyRun_SimpleString( "from time import time,ctime\n"
						"print (ctime(time())) \n");

	ShowWindow(GetConsoleWindow(),SW_MINIMIZE);
	GameManager *game = new GameManager();

	time_t clock=0,past=0,present=0;
	double deltaTime = 0;
	cout << "Wersja OpenGL: " << (const char*)glGetString(GL_VERSION) << "\n";
	QueryPerformanceFrequency(&clock);
	while(true)
	{
		QueryPerformanceCounter(&past);
		game->run(deltaTime);
		QueryPerformanceCounter(&present);
		deltaTime = double(present-past)/clock;
		if(game->isEnd) break;
		_sleep(1);
	}
	delete game;


	Py_Finalize();

	return 0;
}

#define GLFW_DLL

#include "OutputManager.h"


void OutputManager::Run(double deltaTime)
{
	//screen->run(deltaTime);
	glfwSwapInterval(1);
	glfwSwapBuffers();
}

void OutputManager::CreateScene()
{
	screen = new Screen(ScreenWidth,ScreenHeight);
}
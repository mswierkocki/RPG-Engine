#include "MainMenuWindows.h"
#include "Event.h"
#include "utils.h"
#include "Screen.h"

using namespace Input;
using namespace std;

MainMenuWindows::MainMenuWindows(void)
{
	type = WINDOWS_TYPE::MAIN_MENU_WINDOWS;

	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(3);
	tmp[0] = link<Controlka*>((Controlka**)&edytorButton,"edytorButton");
	tmp[2] = link<Controlka*>((Controlka**)&exitGameButton,"exitButton");


	LoadContent("Windows\\MainMenu.xml",tmp);
}

void MainMenuWindows::Update(double deltaTime)
{
	w = screen->getWidth();
	h = screen->getHeight();

	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(newGameButton->pressed)
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::GAME_WORLD_WINDOWS));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::INTERFACE_WINDOWS));
	}

	if(isPressed(27) || exitGameButton->pressed)
		eventQueue.push_back(new ExitEvent());

	if(edytorButton->pressed)
	{
		
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::EDYTOR_WINDOWS));
	}
}

void MainMenuWindows::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();
}
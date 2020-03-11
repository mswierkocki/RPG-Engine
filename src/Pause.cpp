#include "Pause.h"
#include "Event.h"
#include "utils.h"

using namespace Input;


Pause::Pause(void)
{
	loadButton = new ImgButton(this,"Pause_Menu\\load.tga",0,1,Pointf(0,0),Pointf(0.10f,0.15f));
	escButton = new ImgButton(this,"Pause_Menu\\zamknij.tga",0,1,Pointf(0,0),Pointf(0.10f,0));
	backButton = new ImgButton(this,"Pause_Menu\\back.tga",0,1,Pointf(0,0),Pointf(0.10f,-0.15f));
}

void Pause::Draw()
{
	loadButton->Draw();
	escButton->Draw();
	backButton->Draw();
}

void Pause::Update(double deltaTime)
{
	loadButton->Update();
	escButton->Update();
	backButton->Update();

	if(backButton->pressed || isPressed(NULL))
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetActiveEvent(WINDOWS_TYPE::GAME_WORLD_WINDOWS,BOOL_TYPE::SET_TRUE));
		eventQueue.push_back(new SetActiveEvent(WINDOWS_TYPE::INTERFACE_WINDOWS,BOOL_TYPE::SET_TRUE));
	}
	if(escButton->pressed)
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new KillWindowEvent(WINDOWS_TYPE::INTERFACE_WINDOWS));
		eventQueue.push_back(new KillWindowEvent(WINDOWS_TYPE::GAME_WORLD_WINDOWS));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::MAIN_MENU_WINDOWS));
	}
}
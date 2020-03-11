#define GLFW_DLL

#include "GameManager.h"

void GameManager::run(double deltaTime)
{
	outputManager->ClearScene();
	for(unsigned int i = 0; i < windowsQueue.size(); i++)
	{
		if(windowsQueue[i]->isVisible() && windowsQueue[i]->isActive())
			windowsQueue[i]->Update(deltaTime);
	}
	for(unsigned int i = 0; i < windowsQueue.size(); i++)
	{
		if(windowsQueue[i]->isVisible())
			windowsQueue[i]->Draw();
	}
	/////////////////////////
	outputManager->Run(deltaTime);
	/////////////////////////

	for(unsigned int i = 0; i < eventQueue.size(); i++)
	{
		SetActiveEvent* ae;
		SetVisibleEvent* ve;
		KillWindowEvent* ke;
		NewWindowEvent* ne;
		int b;
		switch(eventQueue[i]->Id)
		{
		case EVENT_TYPE::EXIT_EVENT:
			isEnd = true;
			break;
		case EVENT_TYPE::KILL_LAST_EVENT:
			delete windowsQueue[windowsQueue.size()-1];
			windowsQueue.pop_back();
			break;
		case EVENT_TYPE::NEW_WINDOW_EVENT:
			switch (((NewWindowEvent*)eventQueue[i])->windowType)
			{
			case WINDOWS_TYPE::GAME_WORLD_WINDOWS:
				windowsQueue.push_back(new World(gameObjectManager,engine));
				break;
			case WINDOWS_TYPE::INTERFACE_WINDOWS:
				windowsQueue.push_back(new Interface());
				break;
			case WINDOWS_TYPE::MAIN_MENU_WINDOWS:
				windowsQueue.push_back(new MainMenuWindows());
				break;
			case WINDOWS_TYPE::PAUSE_WINDOWS:
				windowsQueue.push_back(new Pause());
				break;
			case WINDOWS_TYPE::EDYTOR_WINDOWS:
				windowsQueue.push_back(new EdytorWindow(engine,gameObjectManager));
				break;
			case WINDOWS_TYPE::OBJECT_WINDOWS:
				ne = (NewWindowEvent*)eventQueue[i];
				windowsQueue.push_back(new ObjectWindow(gameObjectManager,engine,(link<Object>*)(*ne->params)[0]));
				break;
				break;
			case WINDOWS_TYPE::SELECT_TEXTURE_WINDOW:
				ne = (NewWindowEvent*)eventQueue[i];
				windowsQueue.push_back(new SelectTexture(gameObjectManager,(int*)(*ne->params)[0]));
				break;
			case WINDOWS_TYPE::NEW_TEXTURE_WINDOW:
				ne = (NewWindowEvent*)eventQueue[i];
				windowsQueue.push_back(new NewTexture(gameObjectManager,(int*)(*ne->params)[0]));
				break;
			case WINDOWS_TYPE::OLD_TEXTURE_WINDOW:
				ne = (NewWindowEvent*)eventQueue[i];
				windowsQueue.push_back(new OldTexture(gameObjectManager,(int*)(*ne->params)[0]));
				break;
			case WINDOWS_TYPE::OLD_OBJECT_WINDOW:
				windowsQueue.push_back(new OldObject(gameObjectManager,engine));
				break;
			case WINDOWS_TYPE::NEW_MAP_WINDOW:
				ne = (NewWindowEvent*)eventQueue[i];
				windowsQueue.push_back(new NewMap(gameObjectManager,(link<Map>*)(*ne->params)[0]));
				break;
			case WINDOWS_TYPE::OLD_MAP_WINDOW:
				ne = (NewWindowEvent*)eventQueue[i];
				windowsQueue.push_back(new OldMap(gameObjectManager,(int*)(*ne->params)[0]));
				break;
			case WINDOWS_TYPE::ASK_WINDOW:
				ne = (NewWindowEvent*)eventQueue[i];
				windowsQueue.push_back(new AskWindow(*(string*)(*ne->params)[0],(string*)(*ne->params)[1]));
				break;
			case WINDOWS_TYPE::SAVE_WINDOW:
				ne = (NewWindowEvent*)eventQueue[i];
				windowsQueue.push_back(new SaveWindow(gameObjectManager,engine,(bool*)(*ne->params)[0]));
				break;
			}
			break;
		case EVENT_TYPE::SET_ACTIVE_EVENT:
			ae = (SetActiveEvent*)eventQueue[i];
			for (unsigned int j = 0; j<windowsQueue.size();j++)
				if(windowsQueue[j]->getType() == ae->windowType)
				{
					if(ae->setOption == BOOL_TYPE::SET_TRUE) windowsQueue[j]->setActive();
					else if (ae->setOption == BOOL_TYPE::SET_FALSE) windowsQueue[j]->setInActive();
					else windowsQueue[j]->switchActive();
				}
			break;
		case EVENT_TYPE::SET_VISIBLE_EVENT:
			ve = (SetVisibleEvent*)eventQueue[i];
			for (unsigned int j = 0; j<windowsQueue.size();j++)
				if(windowsQueue[j]->getType() == ve->windowType)
				{
					if(ve->setOption == BOOL_TYPE::SET_TRUE) windowsQueue[j]->setVisible();
					else if (ve->setOption == BOOL_TYPE::SET_FALSE) windowsQueue[j]->setInVisible();
					else windowsQueue[j]->switchVisible();
				}
			break;
		case EVENT_TYPE::KILL_WINDOW_EVENT:
			ke = (KillWindowEvent*)eventQueue[i];
			for (unsigned int j = 0; j<windowsQueue.size(); j++)
				if(windowsQueue[j]->getType() == ke->windowType)
				{
					windowsQueue.erase(windowsQueue.begin() + j);
					break;
				}
			break;
		case EVENT_TYPE::SET_ALL_VISIBLE_EVENT:
			b = ((SetAllVisibleEvent*)eventQueue[i])->setOption;
			for (unsigned int j = 0; j<windowsQueue.size(); j++)
			{
				if(b == BOOL_TYPE::SET_TRUE) windowsQueue[j]->setVisible();
				else if (b == BOOL_TYPE::SET_FALSE) windowsQueue[j]->setInVisible();
				else windowsQueue[j]->switchVisible();
			}
			break;
		case EVENT_TYPE::SET_ALL_ACTIVE_EVENT:
			b = ((SetAllActiveEvent*)eventQueue[i])->setOption;
			for (unsigned int j = 0; j<windowsQueue.size(); j++)
			{
				if(b == BOOL_TYPE::SET_TRUE) windowsQueue[j]->setActive();
				else if (b == BOOL_TYPE::SET_FALSE) windowsQueue[j]->setInActive();
				else windowsQueue[j]->switchActive();
			}
			break;
		case EVENT_TYPE::SET_LAST_ACTIVE_EVENT:
			b = ((SetLastActiveEvent*)eventQueue[i])->setOption;
			if(b == BOOL_TYPE::SET_TRUE) windowsQueue.back()->setActive();
			else if (b == BOOL_TYPE::SET_FALSE) windowsQueue.back()->setInActive();
			else windowsQueue.back()->switchActive();
			break;
		}
	}
	eventQueue.clear();
}

OutputManager* GameManager::getOutputManager()
{
	return outputManager;
}

bool GameManager::LoadSettings(){
	Dimension dim;

	if(!cfg.readFile("config.ini")){ 
		if(!cfg.getValue("GraphicsEnv","ScreenWidth",&dim.x))
			dim.x = 800;
	
		if(!cfg.getValue("GraphicsEnv","ScreenHeight",&dim.y))
			dim.x = 600;	
		////////////////////KEYS////////////////////////////
		if(!cfg.getValue("Keys",Input::toggleSkillsMenu->name,&Input::toggleSkillsMenu->z))
			Input::toggleSkillsMenu->z = 'C';

		if(!cfg.getValue("Keys",Input::MoveUp->name,&Input::MoveUp->z))
			Input::MoveUp->z = 'W';

			Input::MoveLeft->z = 'A';
		if(!cfg.getValue("Keys",Input::MoveRight->name,&Input::MoveRight->z))
			Input::MoveRight->z = 'D';

		////////////////////////////////////////////////////
	}
	else{
		cfg.addEntry("GraphicsEnv","ScreenWidth","800");
		cfg.addEntry("GraphicsEnv","ScreenHeight","600");
		////////////////////KEYS////////////////////////////
		cfg.addEntry("Keys",Input::toggleSkillsMenu->name,"P");
		cfg.addEntry("Keys",Input::MoveUp->name,"W");

		cfg.addEntry("Keys",Input::MoveRight->name,"D");
		cfg.addEntry("Keys",Input::MoveLeft->name,"A");
		////////////////////////////////////////////////////
		cfg.saveEntry("config.ini");
		//message("Ponowne uruchomienie programu skorzysta z pliku konfiguracyjnego");
		dim = Dimension(800,600);
	}
	outputManager->setSize(dim);
	
	return true;
}
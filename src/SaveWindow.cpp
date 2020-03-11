#include "SaveWindow.h"
#include "Event.h"

SaveWindow::SaveWindow(GameObjectManager* gom, Engine* engine, bool* wynik):gom(gom),engine(engine),wynik(wynik)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(6);;
	tmp[1] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[2] = link<Controlka*>((Controlka**)&newSaveButton,"newSaveButton");
	tmp[3] = link<Controlka*>((Controlka**)&overSaveButton,"overSaveButton");
	tmp[4] = link<Controlka*>((Controlka**)&cancleButton,"cancleButton");
	tmp[5] = link<Controlka*>((Controlka**)&name,"name");

	LoadContent("Windows\\SaveWindow.xml",tmp);

	if(engine->GetCurrentMap().Id == -1)
		overSaveButton->visible = false;
}

void SaveWindow::Update(double deltatTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();
	
	if(overSaveButton->pressed)
	{
		int id = engine->GetCurrentMap().Id;
		std::link<Map>& map = const_cast<std::link<Map>&>(gom->GetMapByID(id));
		gom->RemoveMapByID(id);
		map = engine->GetCurrentMap();
		engine->SetCurrentMap(gom->CopyMapByID(id));
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_TRUE));
		*wynik = true;
		return;
	}

	if(newSaveButton->pressed)
	{
		engine->SetCurrentMap(gom->AddNewMap(engine->GetCurrentMap(),name->GetText()));
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_TRUE));
		*wynik = true;
		return;
	}

	if(cancleButton->pressed)
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_TRUE));
		*wynik = true;
		return;
	}

	if(backButton->pressed)
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_TRUE));
		*wynik = false;
		return;
	}
}

void SaveWindow::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();
}
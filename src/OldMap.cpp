#include "OldMap.h"


OldMap::OldMap(GameObjectManager* gom, int* id):gom(gom),mapId(id)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(5);
	tmp[0] = link<Controlka*>((Controlka**)&okButton,"okButton");
	tmp[1] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[2] = link<Controlka*>((Controlka**)&delButton,"delButton");
	tmp[3] = link<Controlka*>((Controlka**)&select,"select");
	tmp[4] = link<Controlka*>((Controlka**)&field,"field");

	LoadContent("Windows\\OldMap.xml",tmp);

	vector<string> s;
	for(unsigned int i = 0; i < gom->GetMapVecRef().size(); i++)
	{
		s.push_back(gom->GetMapVecRef()[i].Name);
	}
	select->SetList(s);
	this->id = -1;
}

void OldMap::Update(double deltaTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(okButton->pressed)
	{
		//sprawdzenie poprawnosci
		okButton->pressed = false;
		if(id != -1)
		{
			*mapId = id;
			eventQueue.push_back(new KillLastEvent());
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
		}
	}

	if(backButton->pressed)
	{
		*mapId = -1;
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}
	if(select->IndexChange())
	{
		id = select->GetSelectedIndex();
	}
}

void OldMap::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();
}
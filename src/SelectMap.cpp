#include "SelectMap.h"
#include "Event.h"


void SelectMap::Update(double deltaTime)
{
	nowaMapa->Update();
	wczytajMape->Update();
	okButton->Update();
	backButton->Update();
	idText->Update();
	autoSaveMapa->Update();
	
	if(nowaMapa->pressed)
	{
		nowaMapa->pressed = false;
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = &mapId;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::NEW_MAP_WINDOW,tmp));
	}

	if(wczytajMape->pressed)
	{
		wczytajMape->pressed = false;
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = &mapId;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OLD_MAP_WINDOW,tmp));

	}

	if(backButton->pressed)
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::MAIN_MENU_WINDOWS));
	}

	if(okButton->pressed)
	{
		//sprawdzenie poprawnosci i wybranie mampy dla engina
		//tymczasowo
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::EDYTOR_WINDOWS));
	}
	if(autoSaveMapa->pressed){
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::EDYTOR_WINDOWS));
		gom->LoadAllTextures("Content\\Autosave\\textures.xml");
		gom->LoadAllObjects("Content\\Autosave\\objects.xml");
		gom->LoadAllItems("Content\\Autosave\\items.xml");
		gom->LoadAllCreatures("Content\\Autosave\\creatures.xml");
		gom->LoadAllMaps("Content\\Autosave\\maps.xml");
		engine->SetCurrentMap(gom->GetMapByID(0));
	}
}

void SelectMap::Draw()
{
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,bg->texID);
	Pointf o = getOffset();
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex3f(o.x,		o.y,0);
		glTexCoord2f(1,0); glVertex3f(o.x + w,	o.y,0);
		glTexCoord2f(1,1); glVertex3f(o.x + w,	o.y + h,0);
		glTexCoord2f(0,1); glVertex3f(o.x,		o.y + h,0);
	glEnd();

	glColor3f(0,0,0);
	//WriteText(o.x+4,o.y+110,"Map Id:",15);

	nowaMapa->Draw();
	wczytajMape->Draw();
	okButton->Draw();
	backButton->Draw();
	idText->Draw();
	autoSaveMapa->Draw();
}
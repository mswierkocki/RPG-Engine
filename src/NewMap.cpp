#include "NewMap.h"
#include "Event.h"


NewMap::NewMap(GameObjectManager* gom, link<Map>* map):gom(gom),map(*map)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(9);
	tmp[1] = link<Controlka*>((Controlka**)&okButton,"okButton");
	tmp[2] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[3] = link<Controlka*>((Controlka**)&lButton,"lButton");
	tmp[4] = link<Controlka*>((Controlka**)&rButton,"rButton");
	tmp[5] = link<Controlka*>((Controlka**)&widthBox,"widthBox");
	tmp[6] = link<Controlka*>((Controlka**)&heightBox,"heightBox");
	tmp[7] = link<Controlka*>((Controlka**)&nameBox,"nameBox");
	tmp[8] = link<Controlka*>((Controlka**)&baseField,"baseField");

	LoadContent("Windows\\NewMap.xml",tmp);

	base = 0;
	maxBase = Map::GetBaseCount();
	widthBox->SetText("32");
	heightBox->SetText("32");
	nameBox->SetText("Map" + etos(gom->GetMapVecRef().size() + 1));
}



void NewMap::Update(double deltaTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(lButton->pressed)
	{
		lButton->pressed = false;
		base--;
		if(base<0) base = maxBase - 1;
	}

	if(rButton->pressed)
	{
		rButton->pressed = false;
		base++;
		if(base >= maxBase) base = 0;
	}

	if(okButton->pressed)
	{
		okButton->pressed = false;
		int w = atoi(widthBox->GetText().c_str());
		int h = atoi(heightBox->GetText().c_str());
		string name = nameBox->GetText();
		if(w >= 32 && h >= 32 && name != "")
		{
			map._Ptr = new Map(w,h,base);
			map.Name = name;
			eventQueue.push_back(new KillLastEvent());
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
		}
	}

	if(backButton->pressed)
	{
		map._Ptr = nullptr;
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}
}

void NewMap::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();

	Pointf off, size;
	baseField->CountField(TILESIZE,TILESIZE,off,size);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,Map::GetBase()->texID);
	float x = base / (float)maxBase;
	float dx = 1.0f / (float)maxBase;
	float dy = 1.0f / Map::GetBaseRandom(); 
	glBegin(GL_QUADS);
		glTexCoord2f(x,1-dy);    glVertex2f(off.x       , off.y);
		glTexCoord2f(x+dx,1-dy); glVertex2f(off.x+size.x, off.y);
		glTexCoord2f(x+dx,1); glVertex2f(off.x+size.x, off.y+size.y);
		glTexCoord2f(x,1);    glVertex2f(off.x       , off.y+size.y);
	glEnd();

}


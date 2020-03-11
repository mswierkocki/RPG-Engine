#include "OldTexture.h"
#include <vector>
#include <string>

using namespace std;

OldTexture::OldTexture(GameObjectManager* gom, int* id):Window(460,460,1,1),gom(gom),id(id)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(8);
	tmp[0] = link<Controlka*>((Controlka**)&okButton,"okButton");
	tmp[1] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[2] = link<Controlka*>((Controlka**)&delButton,"delButton");
	tmp[3] = link<Controlka*>((Controlka**)&select,"select");
	tmp[4] = link<Controlka*>((Controlka**)&field,"field");
	tmp[5] = link<Controlka*>((Controlka**)&importButton,"importButton");
	tmp[6] = link<Controlka*>((Controlka**)&searchButton,"searchButton");
	tmp[7] = link<Controlka*>((Controlka**)&filtr,"filtr");

	LoadContent("Windows\\OldTexture.xml",tmp);

	vector<string> s;
	maping.clear();
	for(unsigned int i = 0; i < gom->GetTextureVecRef().size(); i++)
	{
		s.push_back(string(gom->GetTextureVecRef()[i]->file).substr(string(gom->GetTextureVecRef()[i]->file).find("\\")+1));
		maping.push_back(i);
	}
	select->SetList(s);
	newTextureWindow = false;
	tex = nullptr;

	if(*id == -133) okButton->visible = false;
}

void OldTexture::Update(double deltaTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(okButton->pressed)
	{
		//sprawdzenie poprawnosci
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}
	if(searchButton->pressed || filtr->Enter())
	{
		searchButton->pressed = false;
		string f = filtr->GetText();
		vector<string> s;
		maping.clear();
		for(unsigned int i = 0; i < gom->GetTextureVecRef().size(); i++)
		{
			if(string(gom->GetTextureVecRef()[i]->file).find(f) != -1) 
			{
				s.push_back(string(gom->GetTextureVecRef()[i]->file).substr(string(gom->GetTextureVecRef()[i]->file).find("\\")+1));
				maping.push_back(i);
			}
		}
		select->SetList(s);
	}
	if(backButton->pressed)
	{
		*id = -1;
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}
	if(select->IndexChange())
	{
		*id = maping[select->GetSelectedIndex()];
		tex = gom->GetTextureByID(*id)._Ptr;
	}

	if(importButton->pressed)
	{
		importButton->pressed = false;
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = new int();
		newTextureWindow = true;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::NEW_TEXTURE_WINDOW,tmp));
		return;
	}
	if(newTextureWindow)
	{
		newTextureWindow = false;
		vector<string> s;
		for(unsigned int i = 0; i < gom->GetTextureVecRef().size(); i++)
		{
			s.push_back(gom->GetTextureVecRef()[i].Name);
		}
		select->SetList(s);
		newTextureWindow = false;
		tex = nullptr;
	}
}

void OldTexture::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();

	if(tex != nullptr)
	{
		Pointf off, size;
		field->CountField(tex->width,tex->height,off,size);
		glBindTexture(GL_TEXTURE_2D,tex->texID);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(off.x,off.y,0);
			glTexCoord2f(1,0); glVertex3f(off.x+size.x,off.y,0);
			glTexCoord2f(1,1); glVertex3f(off.x+size.x,off.y+size.y,0);
			glTexCoord2f(0,1); glVertex3f(off.x,off.y+size.y,0);
		glEnd();
	}
}


#include "SelectTexture.h"
#include "utils.h"

using namespace Input;


SelectTexture::SelectTexture(GameObjectManager* gom, int* id):gom(gom),textureId(id)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(5);
	tmp[0] = link<Controlka*>((Controlka**)&okButton,"okButton");
	tmp[1] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[2] = link<Controlka*>((Controlka**)&oldButton,"oldButton");
	tmp[3] = link<Controlka*>((Controlka**)&newButton,"newButton");
	tmp[4] = link<Controlka*>((Controlka**)&field,"field");
	LoadContent("Windows\\SelectTexture.xml", tmp);


}


void SelectTexture::Update(double deltaTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(okButton->pressed && *textureId != -1)
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}

	if(backButton->pressed)
	{
		*textureId = -1;
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}

	if(oldButton->pressed)
	{
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = textureId;
		oldButton->pressed = false;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OLD_TEXTURE_WINDOW,tmp));
	}

	if(newButton->pressed)
	{
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = textureId;
		newButton->pressed = false;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::NEW_TEXTURE_WINDOW,tmp));
	}
}

void SelectTexture::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();
	
	if(*textureId != -1)
	{
		Texture* t = gom->GetTextureByID(*textureId);
		Pointf off, size;
		field->CountField(t->width,t->height,off,size);
		glBindTexture(GL_TEXTURE_2D,t->texID);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(off.x,off.y,0);
			glTexCoord2f(1,0); glVertex3f(off.x+size.x,off.y,0);
			glTexCoord2f(1,1); glVertex3f(off.x+size.x,off.y+size.y,0);
			glTexCoord2f(0,1); glVertex3f(off.x,off.y+size.y,0);
		glEnd();
	}
}


#include "NewAnim.h"
#include "Event.h"
#include "utils.h"

NewAnim::NewAnim(GameObjectManager* gom, link<Animation>* a):gom(gom),anim(*a)
{
	id = data_from_window = -1;
	isPlaying = false;
	selectTextureWindow = false;
	type = WINDOWS_TYPE::NEW_ANIM_WINDOWS;

	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(10);
	tmp[0] = link<Controlka*>((Controlka**)&playStopButton,"playStopButton");
	tmp[1] = link<Controlka*>((Controlka**)&okButton,"okButton");
	tmp[2] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[3] = link<Controlka*>((Controlka**)&oldButton,"oldButton");
	tmp[4] = link<Controlka*>((Controlka**)&newButton,"newButton");
	tmp[5] = link<Controlka*>((Controlka**)&textureId,"textureId");
	tmp[6] = link<Controlka*>((Controlka**)&frameCount,"frameCount");
	tmp[7] = link<Controlka*>((Controlka**)&elapseTime,"elapseTime");
	tmp[8] = link<Controlka*>((Controlka**)&name,"name");
	tmp[9] = link<Controlka*>((Controlka**)&field,"field");
	LoadContent("Windows\\NewAnim.xml",tmp);

	if(anim._Ptr != nullptr)//Edit Mode
	{
		id = anim->GetTexture().Id;
		name->SetText(anim.Name);
		textureId->SetText(etos(id));
		frameCount->SetText(etos(anim->GetFrameCount()));
		elapseTime->SetText(etos(1.0/anim->GetFrameSpeed()));
		isPlaying = true;
	}
}

void NewAnim::Update(double deltaTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if (anim != nullptr) anim->Update(deltaTime);

	if(okButton->pressed)
	{
		okButton->pressed = false;
		////////sprawdzic poprawnosc ndanych
		if(anim != nullptr)
		{
			if(name->GetText() != "")
			{
				i_time = 1.0f/atof(elapseTime->GetText().c_str());
				i_frameCount = atoi(frameCount->GetText().c_str());
				if(anim._Ptr != nullptr) delete anim._Ptr;
				anim._Ptr = new Animation(gom->GetTextureByID(id),i_frameCount,i_time);
				anim.Name = name->GetText();
				eventQueue.push_back(new KillLastEvent());
				eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
			}
		}
	}

	if(backButton->pressed)
	{
		if(anim._Ptr != nullptr) { delete anim._Ptr; anim._Ptr = nullptr; }
		id = -1;
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}

	if(newButton->pressed)
	{
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = &data_from_window;
		newButton->pressed = false;
		selectTextureWindow = true;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::NEW_TEXTURE_WINDOW,tmp));
		return;
	}

	if(oldButton->pressed)
	{
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = &data_from_window;
		oldButton->pressed = false;
		selectTextureWindow = true;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OLD_TEXTURE_WINDOW,tmp));
		return;
	}

	if(selectTextureWindow)
	{
		selectTextureWindow = false;
		if(data_from_window != -1)
		{
			id = data_from_window;
			char buff[10];
			textureId->SetText(_itoa(id,buff,10));
			frameCount->SetText("1");
			elapseTime->SetText("32");
			if(anim._Ptr != nullptr) delete anim._Ptr;
			anim._Ptr = new Animation(gom->GetTextureByID(id),1);
			isPlaying = false;
		}
	}

	if(playStopButton->pressed)
	{
		playStopButton->pressed = false;
		isPlaying = !isPlaying;
		if(isPlaying && id != -1)
		{
			i_time = 1.0f/atof(elapseTime->GetText().c_str());
			i_frameCount = atoi(frameCount->GetText().c_str());
			if(anim._Ptr != nullptr) { delete anim._Ptr; anim._Ptr = nullptr;}
			anim._Ptr = new Animation(gom->GetTextureByID(id),i_frameCount,i_time);
		}
	}
}

void NewAnim::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();
	if(id != -1)
	{
		Pointf off, size;
		field->CountField(anim->GetFrameWidth(),anim->GetFrameHeight(),off,size);
		if (isPlaying)
		{
			anim->Draw(off.x,off.y,size.x,size.y);
		}
		else
		{
			anim->Reset();
			anim->Draw(off.x,off.y,size.x,size.y);
		}
	}

}

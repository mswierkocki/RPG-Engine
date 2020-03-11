#include "ObjectViev.h"

using namespace Input;

ObjectView::ObjectView(void)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(9);
	tmp[0] = link<Controlka*>((Controlka**)&lButton,"lButton");
	tmp[1] = link<Controlka*>((Controlka**)&rButton,"rButton");
	tmp[2] = link<Controlka*>((Controlka**)&playButton,"playButton");
	tmp[3] = link<Controlka*>((Controlka**)&nr,"nr");
	tmp[4] = link<Controlka*>((Controlka**)&title,"title");
	tmp[5] = link<Controlka*>((Controlka**)&name,"name");
	tmp[6] = link<Controlka*>((Controlka**)&tag,"tag");
	tmp[7] = link<Controlka*>((Controlka**)&field,"field");
	tmp[8] = link<Controlka*>((Controlka**)&scaleBox,"scaleBox");

	LoadContent("Windows\\ObjectView.xml",tmp);
	object._Ptr = nullptr;
	current._Ptr = nullptr;
	drag = false;
	isPlaying = false;
	animNr = -1;
}

void ObjectView::SetObject(link<Object> o) 
{
	object = o;
	if(object._Ptr != nullptr)
	{
		name->SetText(object.Name);
		tag->SetText("");
		animNr = 0;
		current = new Animation(*object->GetAnimVecRef()[animNr]);
		scaleBox->SetText(etos(object->GetScale()));
	}
	else
	{
		animNr = -1;
		current = nullptr;
		name->SetText("");
	}
}

void ObjectView::SetTitle(string s)
{
	title->SetText(s);
}

void ObjectView::SetVisible()
{
	visible = true;
	if(object._Ptr != nullptr)
	{
		name->SetText(object.Name);
		tag->SetText("");
		animNr = 0;
		current = new Animation(*object->GetAnimVecRef()[animNr]);
		scaleBox->SetText(etos(object->GetScale()));
	}
	else
	{
		animNr = -1;
		current = nullptr;
		name->SetText("");
	}
}

void ObjectView::SetInVisible()
{
	visible = false;
}

void ObjectView::SwitchVisible()
{
	if(visible)
		SetInVisible();
	else
		SetVisible();
}

void ObjectView::Update(double deltaTime)
{
	if(!visible) return;
	if(!active) return;

	int mx = GetX();
	int my = screen->getHeight() - GetY();
	Pointf off = getOffset();
	if(mx > off.x && mx < off.x + w && my > off.y && my < off.y + h )
	{
		InputManager::RestoreMouse();
	}

	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(isPlaying && current != nullptr) current->Update(deltaTime);




	if(lButton->pressed)
	{
		lButton->pressed = false;
		if(object != nullptr)
		{
			animNr--;
			if (animNr < 0) animNr = object->GetAnimVecRef().size() - 1;
			if(current._Ptr != nullptr) delete current._Ptr;
			current = new Animation(*object->GetAnimVecRef()[animNr]);
			nr->SetText(etos(animNr));
		}
	}
	if(scaleBox->Enter())
	{
		object->SetScale(atof(scaleBox->GetText().c_str()));
	}
	if(rButton->pressed)
	{
		rButton->pressed = false;
		if(object != nullptr)
		{
			animNr++;
			if (animNr >= object->GetAnimVecRef().size()) animNr = 0;
			current = new Animation(*object->GetAnimVecRef()[animNr]);
			nr->SetText(etos(animNr));
		}
	}

	if(playButton->pressed)
	{
		playButton->pressed = false;
		isPlaying = !isPlaying;
	}

	if(current != nullptr && focus != scaleBox) scaleBox->SetText(etos(object->GetScale()));

	//////////////////////////////DRAG & DROP///////////////////////////////////
	if(GetButtState(0) == KEY_DOWN)
	{
		if(!drag)
		{
			if(mx > off.x && mx < off.x + w && my > off.y + h - 35 && my < off.y + h )
			{
				drag = true;
				lx = GetX();
				ly = GetY();
			}
		}
		else
		{			
			float dx = GetX() - lx;
			float dy = GetY() - ly;

			offsetPX = offsetPX + Pointf(dx,-dy);

			lx = GetX();
			ly = GetY();

		}
	}
	if(GetButtState(0) == KEY_PRESS)
	{
		drag = false;
	}
	if(mx > off.x && mx < off.x + w && my > off.y && my < off.y + h )
	{
		InputManager::ConsumeMouse();
	}
}

void ObjectView::Draw()
{
	if(!visible) return;
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();

	if(current != nullptr)
	{
		Pointf off, size;
		field->CountField(current->GetFrameWidth(),current->GetFrameHeight(),off,size);
		if(!isPlaying) current->Reset(); //ma NIE byc animowany
		current->Draw(off.x,off.y,size.x,size.y);
	}

}

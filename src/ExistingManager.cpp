#include "ExistingManager.h"
#include "Event.h"

using namespace Input;

ExistingManager::ExistingManager(GameObjectManager* gom, Engine* engine, vector<int>* selected):gom(gom),engine(engine),selected(*selected)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(9);
	tmp[0] = link<Controlka*>((Controlka**)&editButton,"editButton");
	tmp[1] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[2] = link<Controlka*>((Controlka**)&delButton,"delButton");
	tmp[3] = link<Controlka*>((Controlka**)&filtr,"filtr");
	tmp[4] = link<Controlka*>((Controlka**)&searchButton,"searchButton");
	tmp[5] = link<Controlka*>((Controlka**)&multiselect,"multiselect");
	tmp[6] = link<Controlka*>((Controlka**)&minMaxButton,"minMaxButton");
	tmp[7] = link<Controlka*>((Controlka**)&allNoneButton,"allNoneButton");
	tmp[8] = link<Controlka*>((Controlka**)&goToButton,"goToButton");

	LoadContent("Windows\\ExistingManager.xml",tmp);

	objectId = -1;
	editWindow = false;
	visible = false;
	drag = false;
	change = false;
	minim = false;
}

void ExistingManager::SetVisible()
{
	visible = true;
	vector<string> s;
	for(unsigned int i = 0; i < engine->GetCurrentMap()->GetObjectVecRef().size(); i++)
	{
		string n = engine->GetCurrentMap()->GetObjectVecRef()[i].Name;
		
		s.push_back(" " + n.substr(0,10) + "  [rus, aedes]");
	}
	multiselect->SetList(s);
}

void ExistingManager::SetInVisible()
{
	visible = false;
}

void ExistingManager::SwitchVisible()
{
	if(visible)
		SetInVisible();
	else
		SetVisible();
}

bool ExistingManager::IndexChange()
{
	if(change) {change = false; return true;} else return false;
}

void ExistingManager::ForceSelect(int s, bool b)
{
	if(!visible) return;
	if(!multiselect->ForceSelect(s,b))
	{
		SetVisible();
		multiselect->ForceSelect(s,b);
	}
}

void ExistingManager::ClearSelection()
{
	multiselect->ClearSelection();
}

int ExistingManager::GetSelectedIndex()
{
	return multiselect->GetSelectedIndex();
}

void ExistingManager::Update(double deltaTime)
{
	if(!visible) return;
	if(!active) return;
	InputManager::RestoreMouse();
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(minMaxButton->pressed)
	{
		minMaxButton->pressed = false;
		minim = !minim;
		if(minim)
		{
			for(unsigned int i = 0; i < controls.size(); i++) delete controls[i];
			controls.clear();
			vector<link<Controlka*>> tmp = vector<link<Controlka*>>(9);
			tmp[0] = link<Controlka*>((Controlka**)&editButton,"editButton");
			tmp[1] = link<Controlka*>((Controlka**)&backButton,"backButton");
			tmp[2] = link<Controlka*>((Controlka**)&delButton,"delButton");
			tmp[3] = link<Controlka*>((Controlka**)&filtr,"filtr");
			tmp[4] = link<Controlka*>((Controlka**)&searchButton,"searchButton");
			tmp[5] = link<Controlka*>((Controlka**)&multiselect,"multiselect");
			tmp[6] = link<Controlka*>((Controlka**)&minMaxButton,"minMaxButton");
			tmp[7] = link<Controlka*>((Controlka**)&allNoneButton,"allNoneButton");
			tmp[8] = link<Controlka*>((Controlka**)&goToButton,"goToButton");

			LoadContent("Windows\\ExistingManager.xml",tmp);
		}
		else
		{
			for(unsigned int i = 0; i < controls.size(); i++) delete controls[i];
			controls.clear();
			vector<link<Controlka*>> tmp = vector<link<Controlka*>>(9);
			tmp[0] = link<Controlka*>((Controlka**)&editButton,"editButton");
			tmp[1] = link<Controlka*>((Controlka**)&backButton,"backButton");
			tmp[2] = link<Controlka*>((Controlka**)&delButton,"delButton");
			tmp[3] = link<Controlka*>((Controlka**)&filtr,"filtr");
			tmp[4] = link<Controlka*>((Controlka**)&searchButton,"searchButton");
			tmp[5] = link<Controlka*>((Controlka**)&multiselect,"multiselect");
			tmp[6] = link<Controlka*>((Controlka**)&minMaxButton,"minMaxButton");
			tmp[7] = link<Controlka*>((Controlka**)&allNoneButton,"allNoneButton");
			tmp[8] = link<Controlka*>((Controlka**)&goToButton,"goToButton");

			LoadContent("Windows\\ExistingManagerMinim.xml",tmp);
		}
		SetVisible();
		return;
	}

	if(goToButton->pressed)
	{
		goToButton->pressed = false;
		if(objectId != -1 && multiselect->GetSelectedCount() == 1)
		{
			link<Object> o = engine->GetCurrentMap()->GetObjectVecRef()[objectId];
			float sw = screen->getWidth();
			float sh = screen->getHeight();
			float zoom = engine->GetZoom();
			float x = o->GetX() + o->GetCurrentAnim()->GetFrameWidth()*o->GetScale()*0.5f - sw / (2*zoom);
			float y = o->GetY() + o->GetCurrentAnim()->GetFrameHeight()*o->GetScale()*0.5f - sh / (2*zoom);
			engine->SetMapPos(Pointf(x,y));
		}
	}

	////////////////////////////////////////EDIT//////////////////////////////
	if(editButton->pressed)
	{
		editButton->pressed = false;
		if(objectId != -1 && multiselect->GetSelectedCount() == 1)
		{
			
			editWindow = true;
			//skopiowac obiekt
			const link<Object>& ref = gom->GetObjectByID(objectId);
			object = link<Object>(new Object(*ref),ref.Name,ref.Id);
			//
			vector<void*>* tmp = new vector<void*>(1);
			(*tmp)[0] = &object;
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OBJECT_WINDOWS,tmp));		//wywolanie okna edycji;
			return;
		}
	}
	if(editWindow)
	{
		editWindow = false;
		if(object._Ptr != nullptr)
		{
			//odkopiowac obiekt
			link<Object>& ref = const_cast<link<Object>&>(gom->GetObjectByID(objectId)); 
			delete ref._Ptr;
			ref = object;
		}
	}

	if(delButton->pressed)
	{
		delButton->pressed = false;
		if(objectId != -1 && multiselect->GetSelectedCount() == 1)
		{
			delete engine->GetCurrentMap()->GetObjectVecRef()[objectId]; //usun animacje 
			engine->GetCurrentMap()->GetObjectVecRef().erase(engine->GetCurrentMap()->GetObjectVecRef().begin() + objectId); 
		}
	}
	//////////////////////////////
	if(multiselect->IndexChange())
	{
		objectId = multiselect->GetSelectedIndex();
		int t = multiselect->GetSelectedType();
		if(t == 0)
		{
			selected.clear();
			selected.push_back(objectId);
		}
		else if(t == 1)
		{
			selected.push_back(objectId);
		}
		else
		{
			for(unsigned int i = 0; i < selected.size(); i++)
				if(selected[i] == objectId) {selected.erase(selected.begin() + i); break;}
		}
		change = true;
	}

	if(backButton->pressed)
	{
		backButton->pressed = false;
		visible = false;
		drag = false;
		return;
	}
	
	int mx = GetX();
	int my = screen->getHeight() - GetY();
	Pointf off = getOffset();

	if(!drag)
	{
		if(mx > off.x && mx < off.x + w && my > off.y + h - 45 && my < off.y + h && GetButtPressed(0))
		{
			drag = true;
			lx = GetX();
			ly = GetY();
		}
	}
	else
	{
		offsetPX = offsetPX + Pointf(GetX() - lx, ly - GetY());
		lx = GetX();
		ly = GetY();
	}
	if(GetButtState(0) == KEY_PRESS)
	{
		drag = false;
	}

	////////////////////////////////////////////////////
	if(mx > off.x && mx < off.x + w && my > off.y && my < off.y + h )
	{
		InputManager::ConsumeMouse();
	}
}

void ExistingManager::Draw()
{
	if(!visible) return;
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();
}
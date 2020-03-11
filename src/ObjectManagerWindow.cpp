#include "ObjectManagerWindow.h"
#include "Event.h"

using namespace Input;

ObjectManagerWindow::ObjectManagerWindow(GameObjectManager* gom, Engine* engine):gom(gom),engine(engine)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(9);
	tmp[0] = link<Controlka*>((Controlka**)&o_addButton,"o_addButton");
	tmp[1] = link<Controlka*>((Controlka**)&o_backButton,"o_backButton");
	tmp[2] = link<Controlka*>((Controlka**)&o_delButton,"o_delButton");
	tmp[3] = link<Controlka*>((Controlka**)&o_editButton,"o_editButton");
	tmp[4] = link<Controlka*>((Controlka**)&o_filtr,"o_filtr");
	tmp[5] = link<Controlka*>((Controlka**)&o_importButton,"o_importButton");
	tmp[6] = link<Controlka*>((Controlka**)&o_searchButton,"o_searchButton");
	tmp[7] = link<Controlka*>((Controlka**)&o_select,"o_select");
	tmp[8] = link<Controlka*>((Controlka**)&o_minMaxButton,"o_minMaxButton");

	LoadContent("Windows\\ObjectManager.xml",tmp);

	o_objectId = -1;
	o_editWindow = false;
	visible = false;
	drag = false;
	change = false;
	minim = false;
}

void ObjectManagerWindow::SetVisible()
{
	visible = true;
	vector<string> s;
	for(unsigned int i = 0; i < gom->GetObjectVecRef().size(); i++)
	{
		string n = gom->GetObjectVecRef()[i].Name;
		
		s.push_back(" " + n.substr(0,10) + "  [rus, aedes]");
	}
	o_select->SetList(s);
}

void ObjectManagerWindow::SetInVisible()
{
	visible = false;
}

void ObjectManagerWindow::SwitchVisible()
{
	if(visible)
		SetInVisible();
	else
		SetVisible();
}

bool ObjectManagerWindow::IndexChange()
{
	if(change) {change = false; return true;} else return false;
}

int ObjectManagerWindow::GetSelectedIndex()
{
	return o_select->GetSelectedIndex();
}

void ObjectManagerWindow::Update(double deltaTime)
{
	InputManager::RestoreMouse();
	if(!visible) return;
	if(!active) return;
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();
	////////////////////////MINIM////////////////
	if(o_minMaxButton->pressed)
	{
		o_minMaxButton->pressed = false;
		minim = !minim;
		if(minim)
		{
			for(unsigned int i = 0; i < controls.size(); i++) delete controls[i];
			controls.clear();
			vector<link<Controlka*>> tmp = vector<link<Controlka*>>(9);
			tmp[0] = link<Controlka*>((Controlka**)&o_addButton,"o_addButton");
			tmp[1] = link<Controlka*>((Controlka**)&o_backButton,"o_backButton");
			tmp[2] = link<Controlka*>((Controlka**)&o_delButton,"o_delButton");
			tmp[3] = link<Controlka*>((Controlka**)&o_editButton,"o_editButton");
			tmp[4] = link<Controlka*>((Controlka**)&o_filtr,"o_filtr");
			tmp[5] = link<Controlka*>((Controlka**)&o_importButton,"o_importButton");
			tmp[6] = link<Controlka*>((Controlka**)&o_searchButton,"o_searchButton");
			tmp[7] = link<Controlka*>((Controlka**)&o_select,"o_select");
			tmp[8] = link<Controlka*>((Controlka**)&o_minMaxButton,"o_minMaxButton");
			LoadContent("Windows\\ObjectManagerMinim.xml",tmp);
		}
		else
		{
			for(unsigned int i = 0; i < controls.size(); i++) delete controls[i];
			controls.clear();
			vector<link<Controlka*>> tmp = vector<link<Controlka*>>(9);
			tmp[0] = link<Controlka*>((Controlka**)&o_addButton,"o_addButton");
			tmp[1] = link<Controlka*>((Controlka**)&o_backButton,"o_backButton");
			tmp[2] = link<Controlka*>((Controlka**)&o_delButton,"o_delButton");
			tmp[3] = link<Controlka*>((Controlka**)&o_editButton,"o_editButton");
			tmp[4] = link<Controlka*>((Controlka**)&o_filtr,"o_filtr");
			tmp[5] = link<Controlka*>((Controlka**)&o_importButton,"o_importButton");
			tmp[6] = link<Controlka*>((Controlka**)&o_searchButton,"o_searchButton");
			tmp[7] = link<Controlka*>((Controlka**)&o_select,"o_select");
			tmp[8] = link<Controlka*>((Controlka**)&o_minMaxButton,"o_minMaxButton");
			LoadContent("Windows\\ObjectManager.xml",tmp);
		}
		SetVisible();
		return;
	}

	////////////////////////////////////////EDIT//////////////////////////////
	if(o_editButton->pressed)
	{
		o_editButton->pressed = false;
		if(o_objectId != -1)
		{
			
			o_editWindow = true;
			//skopiowac obiekt
			const link<Object>& ref = gom->GetObjectByID(o_objectId);
			o_object = link<Object>(new Object(ref->GetX(),ref->GetY(),ref->GetScale()),ref.Name,ref.Id);
			for(unsigned i=0; i<ref->GetAnimVecRef().size(); i++)
				o_object->GetAnimVecRef().push_back(new Animation(*ref->GetAnimVecRef().at(i)));
			//
			vector<void*>* tmp = new vector<void*>(1);
			(*tmp)[0] = &o_object;
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OBJECT_WINDOWS,tmp));		//wywolanie okna edycji;
			return;
		}
	}
	if(o_editWindow)
	{
		o_editWindow = false;
		if(o_object._Ptr != nullptr)
		{
			//odkopiowac obiekt
			link<Object>& ref = const_cast<link<Object>&>(gom->GetObjectByID(o_objectId));
			for(unsigned i=0; i<ref->GetAnimVecRef().size(); i++)
				delete ref->GetAnimVecRef()[i]._Ptr;
			delete ref._Ptr;
			ref = o_object;
		}
	}
	/////////////////////////////DODAJ OBIEKT Z OBJECT MANAGERA////////////////////
	if(o_addButton->pressed)
	{
		o_addButton->pressed = false;
		if(o_objectId != -1 && engine->HasMap())
		{
			//sprawdzenie poprawnosci i dodanie do engine
			engine->GetCurrentMap()->GetObjectVecRef().push_back(gom->CopyObjectByID(o_objectId));
			engine->GetCurrentMap()->GetObjectVecRef().back()->Set(engine->GetMapCoords().x + screen->getWidth() / (2  *engine->GetZoom()), engine->GetMapCoords().y + screen->getHeight() / (2 * engine->GetZoom()));
			return;
		}
	}
	//////////////////////////////
	if(o_select->IndexChange())
	{
		o_objectId = o_select->GetSelectedIndex();
		change = true;
	}

	if(o_backButton->pressed)
	{
		o_backButton->pressed = false;
		visible = false;
		drag = false;
		return;
	}
	if(o_importButton->pressed)
	{
		o_importButton->pressed = false;
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = new link<Object>();
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OBJECT_WINDOWS,tmp));
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

void ObjectManagerWindow::Draw()
{
	if(!visible) return;
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();
}
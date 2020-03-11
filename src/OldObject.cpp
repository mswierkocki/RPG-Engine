#include "OldObject.h"
#include <vector>
#include <string>

using namespace std;

OldObject::OldObject(GameObjectManager* gom, Engine* engine):gom(gom),engine(engine)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(6);
	tmp[0] = link<Controlka*>((Controlka**)&addButton,"addButton");
	tmp[1] = link<Controlka*>((Controlka**)&editButton,"editButton");
	tmp[2] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[3] = link<Controlka*>((Controlka**)&delButton,"delButton");
	tmp[4] = link<Controlka*>((Controlka**)&select,"select");
	tmp[5] = link<Controlka*>((Controlka**)&field,"field");

	LoadContent("Windows\\OldObject.xml",tmp);

	editWindow = false;
	objectId = -1;

	vector<string> s;
	for(unsigned int i = 0; i < gom->GetObjectVecRef().size(); i++)
	{
		s.push_back(gom->GetObjectVecRef()[i].Name);
	}
	select->SetList(s);
}

void OldObject::Update(double deltaTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(addButton->pressed)
	{
		addButton->pressed = false;
		if(objectId != -1)
		{
			//sprawdzenie poprawnosci i dodanie do engine
			engine->GetCurrentMap()->GetObjectVecRef().push_back(gom->CopyObjectByID(objectId));
			eventQueue.push_back(new KillLastEvent());
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
			return;
		}
	}

	if(editButton->pressed)
	{
		editButton->pressed = false;
		if(objectId != -1)
		{
			
			editWindow = true;
			//skopiowac obiekt
			const link<Object>& ref = gom->GetObjectByID(objectId);
			object = link<Object>(new Object(ref->GetX(),ref->GetY(),ref->GetScale()),ref.Name,ref.Id);
			for(unsigned i=0; i<ref->GetAnimVecRef().size(); i++)
				object->GetAnimVecRef().push_back(new Animation(*ref->GetAnimVecRef().at(i)));
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
			for(unsigned i=0; i<ref->GetAnimVecRef().size(); i++)
				delete ref->GetAnimVecRef()[i]._Ptr;
			delete ref._Ptr;
			ref = object;
		}
	}

	if(backButton->pressed)
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
		return;
	}

	if(select->IndexChange())
	{
		objectId = select->GetSelectedIndex();
	}
}

void OldObject::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();
	
	if(objectId != -1)
	{
		const link<Object>& ref = gom->GetObjectByID(objectId);
		link<Animation> anim = ref->GetAnimVecRef()[0];
		anim->Reset();
		Pointf off, size;
		field->CountField(anim->GetFrameWidth(),anim->GetFrameHeight(),off,size);
		anim->Draw(off.x,off.y,size.x,size.y);

	}
}



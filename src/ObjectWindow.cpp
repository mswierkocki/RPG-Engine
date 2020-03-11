#include "ObjectWindow.h"
#include "Event.h"
#include "utils.h"

using namespace Input;

ObjectWindow::ObjectWindow(GameObjectManager* gom, Engine* engine, link<Object>* o):object(*o),gom(gom),engine(engine)
{
	type = WINDOWS_TYPE::OBJECT_WINDOWS;
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(16);
	tmp[0] = link<Controlka*>((Controlka**)&addAnim,"addAnim");
	tmp[1] = link<Controlka*>((Controlka**)&delAnim,"delAnim");
	tmp[2] = link<Controlka*>((Controlka**)&startPoli,"startPoli");
	tmp[3] = link<Controlka*>((Controlka**)&stopPoli,"stopPoli");
	tmp[4] = link<Controlka*>((Controlka**)&playAnim,"playAnim");
	tmp[5] = link<Controlka*>((Controlka**)&okButton,"okButton");
	tmp[6] = link<Controlka*>((Controlka**)&name,"name");
	tmp[7] = link<Controlka*>((Controlka**)&tag,"tag");
	tmp[8] = link<Controlka*>((Controlka**)&field,"field");
	tmp[9] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[10] = link<Controlka*>((Controlka**)&select,"select");
	tmp[11] = link<Controlka*>((Controlka**)&editAnim,"editAnim");
	tmp[12] = link<Controlka*>((Controlka**)&startPoli2,"startPoli2");
	tmp[13] = link<Controlka*>((Controlka**)&stopPoli2,"stopPoli2");
	tmp[14] = link<Controlka*>((Controlka**)&scriptBox,"scriptBox");
	tmp[15] = link<Controlka*>((Controlka**)&classBox,"classBox");

	LoadContent("Windows\\ObjectEditor.xml", tmp);

	current = nullptr;
	newAnimWindow = false;
	isPlaying = false;
	animNr = -1;
	if(object == nullptr)
	{
		object._Ptr = new Object();
		czyEdycja = false;
	}
	else
	{
		czyEdycja = true;
		name->SetEnable(false);
		animNr = 0;
		current = object->GetAnimVecRef()[animNr];
		name->SetText(object.Name);
		scriptBox->SetText(object->GetScriptName());
		classBox->SetText(object->GetClassName());
		vector<string> s;
		for(unsigned int i =0; i < object->GetAnimVecRef().size(); i++)
		{
			s.push_back(object->GetAnimVecRef()[i].Name);
		}
		select->SetList(s);
		select->ForceSelect(0);
	}
	drag = false;
	polygon = new Poly();
	creatingCollisio = false;
	creatingOcllusion = false;
	drawCollisio = true;
	drawOcllusion = true;
}

void ObjectWindow::Update(double deltaTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();
	int mx = GetX();
	int my = screen->getHeight() - GetY();

	if(isPlaying) current->Update(deltaTime);

	if(newAnimWindow)
	{
		newAnimWindow = false;
		if(anim != nullptr)
		{
			object->GetAnimVecRef().push_back(anim);
			animNr = object->GetAnimVecRef().size() - 1;
			isPlaying = true;
			current = object->GetAnimVecRef()[animNr];
			vector<string> s;
			for(unsigned int i =0; i < object->GetAnimVecRef().size(); i++) s.push_back(object->GetAnimVecRef()[i].Name);
			select->SetList(s);
			select->ForceSelect(animNr);
		}
	}

	if(editAnimWindow)
	{
		editAnimWindow = false;
		if(anim != nullptr)
		{
			delete object->GetAnimVecRef()[animNr]._Ptr;
			object->GetAnimVecRef()[animNr] = anim;
			current = object->GetAnimVecRef()[animNr];
			vector<string> s;
			for(unsigned int i =0; i < object->GetAnimVecRef().size(); i++) s.push_back(object->GetAnimVecRef()[i].Name);
			select->SetList(s);
			select->ForceSelect(animNr);
		}
	}

	if(select->IndexChange())
	{
		isPlaying = false;
		animNr = select->GetSelectedIndex();
		current = object->GetAnimVecRef()[animNr];
	}


	if(delAnim->pressed)
	{
		delAnim->pressed = false;
	}

	///////////////////////////////////COLLISION////////////////////////////////
	if((creatingCollisio || creatingOcllusion) && animNr != -1)
	{
		Pointf off, size;
		field->CountField(current->GetFrameWidth(),current->GetFrameHeight(),off,size);
		if(mx > off.x && mx < off.x + size.x && my > off.y && my < off.y + size.y && GetButtPressed(0))
		{
			polygon->points.push_back(Pointf(mx - off.x, my - off.y, 0));
			if(polygon->points.size() > 1)
			{
				float r = sqrt((mx-off.x - polygon->points[0].x)*(mx-off.x - polygon->points[0].x) + (my-off.y - polygon->points[0].y)*(my-off.y - polygon->points[0].y));
				if(r <= 3)
				{
					if(polygon->points.size() >= 2) 
					{
						polygon->points.back() = polygon->points[0];
						polygon->BuildEdges();
						if(creatingCollisio)
							object->SetCollision(polygon);
						else
							object->SetOcclusion(polygon);
						polygon = nullptr;
					}
					else
					{
						if(creatingCollisio)
							object->SetCollision(nullptr);
						else
							object->SetOcclusion(nullptr);
						delete polygon;
						polygon = nullptr;
					}
					creatingCollisio = creatingOcllusion = false;
				}
			}  
		}
	}
	if(startPoli->pressed && !creatingCollisio && !creatingOcllusion)
	{
		startPoli->pressed = false;
		creatingCollisio = true;
		if(polygon != nullptr) delete polygon;
		polygon = new Poly();
		GetButtPressed(0);
	}
	if(stopPoli->pressed)
	{
		stopPoli->pressed = false;
		creatingCollisio = false;
		object->SetCollision(nullptr);
		if(polygon != nullptr) delete polygon;
		polygon = nullptr;
	}
	////////////////////////OCCLUSION///////////////////////////////
	if(startPoli2->pressed && !creatingCollisio && !creatingOcllusion)
	{
		startPoli2->pressed = false;
		creatingOcllusion = true;
		if(polygon != nullptr) delete polygon;
		polygon = new Poly();
		GetButtPressed(0);
	}
	if(stopPoli2->pressed)
	{
		stopPoli2->pressed = false;
		creatingOcllusion = false;
		object->SetOcclusion(nullptr);
		if(polygon != nullptr) delete polygon;
		polygon = nullptr;
	}
	//////////////////////////////////////////////////////////////////////////////////
	if(editAnim->pressed)
	{
		if(animNr != -1)
		{
			editAnimWindow = true;
			editAnim->pressed = false;
			vector<void*>* tmp = new vector<void*>(1);
			//skopiowac aktualna animacje
			anim = link<Animation>();
			anim.Id = current.Id;
			anim.Name = current.Name;
			anim._Ptr = new Animation(current->GetTexture(),current->GetFrameCount(),current->GetFrameSpeed());
			anim->SetAnimSpeed(current->GetAnimSpeed());
			(*tmp)[0] = &anim;
			eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::NEW_ANIM_WINDOWS,tmp));
			return;
		}
	}

	if(addAnim->pressed)
	{
		newAnimWindow = true;
		addAnim->pressed = false;
		vector<void*>* tmp = new vector<void*>(1);
		anim = link<Animation>();
		(*tmp)[0] = &anim;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::NEW_ANIM_WINDOWS,tmp));
		return;
	}

	if(backButton->pressed)
	{
		if(object._Ptr != nullptr) { delete object._Ptr; object._Ptr = nullptr; animNr = -1;}
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_TRUE));
		return;
	}

	if (playAnim->pressed)
	{
		playAnim->pressed = false;
		if(animNr != -1)
		{
			isPlaying = !isPlaying;
			if(isPlaying)
			{
				current = object->GetAnimVecRef()[animNr];
			}
		}
	}

	if (okButton->pressed)
	{
		if(czyEdycja)
		{
			////////////////EDYCJA////////////////////////////////
			eventQueue.push_back(new KillLastEvent());
			eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_TRUE));
		}
		else
		{
			///////////////NOWY//////////////////////////////////
			//jesli niema animacji to jeb sie
			object->SetScriptName(scriptBox->GetText());
			object->SetClassName(classBox->GetText());
			link<Object> o = gom->AddNewObject(object, name->GetText());
			engine->GetCurrentMap()->GetObjectVecRef().push_back(gom->CopyObjectByID(o.Id));
			eventQueue.push_back(new KillLastEvent());
			eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_TRUE));
		}
		return;
	}

	//////////////////////////////////////
	Pointf off = getOffset();

	if(GetButtState(0) == KEY_DOWN)
	{
		if(!drag)
		{
			if(mx > off.x && mx < off.x + w && my > off.y + h - 10 && my < off.y + h )
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
}

void ObjectWindow::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();

	if(animNr != -1) //jest co narysowac
	{
		Pointf off, size;
		field->CountField(current->GetFrameWidth(),current->GetFrameHeight(),off,size);
		if(isPlaying) //ma byc animowany
		{
			current->Draw(off.x,off.y,size.x,size.y);
		}
		else
		{
			current->Reset();
			current->Draw(off.x,off.y,size.x,size.y);
		}
	}

	if((creatingCollisio || creatingOcllusion) && animNr != -1)
	{
		int mx = GetX();
		int my = screen->getHeight() - GetY();
		Pointf off, size;
		field->CountField(current->GetFrameWidth(),current->GetFrameHeight(),off,size);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1,0.80f,0.05f);
		if(polygon->points.size() >= 1)
		{
			glPointSize(6);
			glBegin(GL_POINTS);
				glVertex3fv((off + polygon->points[0]));
			glEnd();
		}
		glBegin(GL_LINE_STRIP);
			for(unsigned int i = 0; i < polygon->points.size(); i++)
			{
				glVertex3fv((off + polygon->points[i]));
			}
			if(mx > off.x && mx < off.x + size.x && my > off.y && my < off.y + size.y)
				glVertex3f(mx, my, 0);
		glEnd();

		glEnable(GL_TEXTURE_2D);
	}
	if(drawCollisio && !creatingCollisio && animNr != -1 && object->GetCollision() != nullptr)
	{
		Pointf off, size;
		field->CountField(current->GetFrameWidth(),current->GetFrameHeight(),off,size);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.6f,0.05f,0.02f);
		glBegin(GL_LINE_STRIP);
			for(unsigned int i = 0; i < object->GetCollision()->points.size(); i++)
			{
				glVertex3fv((off + object->GetCollision()->points[i]));
			}
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}
	if(drawOcllusion && !creatingOcllusion && animNr != -1 && object->GetOcclusion() != nullptr)
	{
		Pointf off, size;
		field->CountField(current->GetFrameWidth(),current->GetFrameHeight(),off,size);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.8f,0.8f,0.8f);
		glBegin(GL_LINE_STRIP);
			for(unsigned int i = 0; i < object->GetOcclusion()->points.size(); i++)
			{
				glVertex3fv((off + object->GetOcclusion()->points[i]));
			}
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}
}



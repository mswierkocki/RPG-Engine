#include "EdytorWindow.h"
#include "utils.h"
#include "Event.h"
#include <algorithm>

using namespace Input;


EdytorWindow::EdytorWindow(Engine* e,GameObjectManager* gom):engine(e),gom(gom)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(19);
	tmp[0] = link<Controlka*>((Controlka**)&newMapButton,"newMapButton");
	tmp[1] = link<Controlka*>((Controlka**)&oldMapButton,"oldMapButton");
	tmp[2] = link<Controlka*>((Controlka**)&saveButton,"saveButton");
	tmp[3] = link<Controlka*>((Controlka**)&saveAsButton,"saveAsButton");
	tmp[4] = link<Controlka*>((Controlka**)&objectManagerButton,"objectManagerButton");
	tmp[5] = link<Controlka*>((Controlka**)&viewButton,"viewButton");
	tmp[6] = link<Controlka*>((Controlka**)&properties,"properties");
	tmp[7] = link<Controlka*>((Controlka**)&scriptEditor,"scriptEditor");
	tmp[8] = link<Controlka*>((Controlka**)&mapSettings,"mapSettings");
	tmp[9] = link<Controlka*>((Controlka**)&zoomInButton,"zoomInButton");
	tmp[10] = link<Controlka*>((Controlka**)&zoomOutButton,"zoomOutButton");
	tmp[11] = link<Controlka*>((Controlka**)&objectListButton,"objectListButton");
	tmp[12] = link<Controlka*>((Controlka**)&zoom100Button,"zoom100Button");
	tmp[13] = link<Controlka*>((Controlka**)&playButton,"playButton");
	tmp[14] = link<Controlka*>((Controlka**)&stopButton,"stopButton");
	tmp[15] = link<Controlka*>((Controlka**)&texturesButton,"texturesButton");
	tmp[16] = link<Controlka*>((Controlka**)&terrainButton,"terrainButton");
	tmp[17] = link<Controlka*>((Controlka**)&gridButton,"gridButton");
	tmp[18] = link<Controlka*>((Controlka**)&resetButton,"resetButton");

	LoadContent("Windows\\Edytor.xml",tmp);

	bar = new Texture("Edytor\\dockbar.png");
	bar2 = new Texture("Edytor\\downbar.png");

	editWindow = false;
	newMapWindow = false;
	oldMapWindow = false;
	saveAsWindow = false;
	saveForNew = false;
	saveForOld = false;
	gridVisible = false;
	selected.clear();
	drag = mpress = grab = false;
	engine->SetPolygonsMode(true);

	manager = new ObjectManagerWindow(gom,engine);
	manager->SetInVisible();

	view = new ObjectView();
	view->SetInVisible();

	existing = new ExistingManager(gom,engine,&selected);
	existing->SetInVisible();

	terrain = new TerrainTools(engine);
	terrain->SetInVisible();

	isPlaying = false;
	kolejnosc = -1;
}

void EdytorWindow::Update(double deltaTime)
{
	this->w = screen->getWidth();
	this->h = screen->getHeight();
	//bar->SetWidth(this->w);

	manager->Update(deltaTime);
	existing->Update(deltaTime);
	view->Update(deltaTime);
	terrain->Update(deltaTime);

	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();
	if(isPlaying) engine->Update(deltaTime);

	float speed = 5.0f;

	if(isDown(MoveDown))
	{
		engine->MoveMap(Pointf(0,-speed));
	}
	if(isDown(MoveRight))
	{
		engine->MoveMap(Pointf(speed,0));
	}
	if(isDown(MoveLeft))
	{
		engine->MoveMap(Pointf(-speed,0));
	}
	if(isDown(MoveUp))
	{
		engine->MoveMap(Pointf(0,speed));
	}

	if(isDown('Z',true))
	{
		engine->Zoom(1);
	}

	if(isDown('X',true))
	{
		engine->Zoom(-1);
	}

	/////////////////////////////////////////DRAG & DROP & WHEEL/////////////////////////
	if(isDown(GLFW_KEY_LCTRL))
	{
		/////// MOUSE WHEEL ///////
		float dw = glfwGetMouseWheel() - lw;
		//std::cout << glfwGetMouseWheel() << "  ,   "  << dw << endl;
		if(abs(dw) > 0.9 && selected.size() != 0) 
		{
			float sx = 0, sy = 0;
			vector<link<Object>>& obj = engine->GetCurrentMap()->GetObjectVecRef();
			for(unsigned int i = 0; i < selected.size(); i++)
			{
				sx += obj[selected[i]]->GetX();
				sy += obj[selected[i]]->GetY();
			}
			sx /= selected.size();
			sy /= selected.size();
			for(unsigned int i = 0; i < selected.size(); i++)
			{
				float x = obj[selected[i]]->GetX();
				float y = obj[selected[i]]->GetY();
				float ratio = (obj[selected[i]]->GetScale() + dw/60.0f) / obj[selected[i]]->GetScale();
				obj[selected[i]]->Set((x - sx)*ratio + sx, (y - sy)*ratio + sy);
				obj[selected[i]]->SetScale(obj[selected[i]]->GetScale() + dw/60.0f);
			}
		}
		lw = glfwGetMouseWheel();
	}
	else
	{
		/////// MOUSE WHEEL ///////
		int dw = glfwGetMouseWheel() - lw;
		//if(abs(dw) > 0.9f) engine->Zoom(1 - 0.1f*dw);
		if(abs(dw) > 0.9f) engine->Zoom(dw);
		lw = glfwGetMouseWheel();
	}
	//if(drag) InputManager::RestoreMouse();

	if(GetButtPressed(2) && engine->HasMap()/* || (!drag && GetButtPressed(1) && engine->HasMap())*/)
	{
		lx = GetX();
		ly = GetY();
		grab = true;
	}
	if(grab)
	{
		int dx = GetX() - lx;
		int dy = GetY() - ly;		

		engine->MoveMap(Pointf(-dx/engine->GetZoom(),dy/engine->GetZoom()));
		
		lx = GetX();
		ly = GetY();

		if(GetButtState(2) == KEY_PRESS) grab = false;
		//if(GetButtState(1) == KEY_PRESS) grab = false;
	}

	if(GetButtState(0) == KEY_DOWN && terrain->isVisible() && GetY() > 60)
	{
		int x = (int)(GetX() / engine->GetZoom() + engine->GetMapCoords().x) / TILESIZE;
		int y = (int)((screen->getHeight() - GetY()) / engine->GetZoom() + engine->GetMapCoords().y) / TILESIZE;
		terrain->Set(x,y);
	}

	if(!drag)
	{
		if(GetButtState(0) == KEY_DOWN && !mpress)
		{
			mpress = true;
			if(terrain->isVisible())
				return;
			vector<int> tmp = engine->GetObjectsIdUnderMouse();
			if(tmp.size() > 0)
			{
				if(isDown(GLFW_KEY_LALT)) kolejnosc++;
				if(kolejnosc >= tmp.size()) kolejnosc = 0;
				bool first = true;
				if(isDown(GLFW_KEY_LCTRL))
				{
					for(unsigned int i = 0; i < selected.size(); i++)
						if(selected[i] == tmp[kolejnosc]) { selected.erase(selected.begin() + i); existing->ForceSelect(tmp[kolejnosc],false); first = false; break; }
					if(first) //pirwsze nacisniecie
					{
						//if(!isDown(GLFW_KEY_LCTRL)) selected.clear();
						selected.push_back(tmp[kolejnosc]);
						existing->ForceSelect(tmp[kolejnosc],true);
						view->SetTitle("SELECTED OBJECT");
						view->SetObject(engine->GetCurrentMap()->GetObjectVecRef()[tmp[kolejnosc]]);
					}
				}
				else
				{
					int dx = GetX() - lx;
					int dy = GetY() - ly;
					for(unsigned int i = 0; i < selected.size(); i++)
						if(selected[i] == tmp[kolejnosc]) { first = false; break; }
					if(first) //pirwsze nacisniecie
					{
						selected.clear(); existing->ClearSelection();
						selected.push_back(tmp[kolejnosc]);
						existing->ForceSelect(tmp[kolejnosc],true);
						view->SetTitle("SELECTED OBJECT");
						view->SetObject(engine->GetCurrentMap()->GetObjectVecRef()[tmp[kolejnosc]]);
					}
					else //drogie nacisniecie
					{
						//if(lx != GetX() || ly != GetY())
						//{
							lx = GetX();
							ly = GetY();
							drag = true;
							manager->setInActive();
							view->setInActive();
						//}
					}
				}
			}
			else
			{
				selected.clear();
				existing->ClearSelection();
				view->SetTitle("VIEWER");
				view->SetObject(nullptr);
			}
			//lx = GetX();
			//ly = GetY();
		}
	}
	else
	{
		float dx = GetX() - lx;
		float dy = GetY() - ly;
			
		//DRAG&DROP
		int w = engine->GetCurrentMap()->GetW(), sw = screen->getWidth();
		int h = engine->GetCurrentMap()->GetH(), sh = screen->getHeight();
		float zoom = engine->GetZoom();

		vector<link<Object>>& obj = engine->GetCurrentMap()->GetObjectVecRef();
		for(unsigned int i = 0; i < selected.size(); i++)
			obj[selected[i]]->Set(obj[selected[i]]->GetX() + dx / zoom,obj[selected[i]]->GetY() - dy / zoom);
		lx = GetX();
		ly = GetY();
	}
	if(GetButtState(0) == KEY_PRESS)
	{
		drag = false;
		mpress = false;
		manager->setActive();
		view->setActive();
	}

	//if(GetButtState(0) == KEY_DOWN)
	//{
	//	//cout << ".";
	//	if(!drag)
	//	{
	//		//cout << ",";
	//		vector<link<Object>*> tmp = engine->GetObjectsUnderMouse();
	//		if(tmp.size() > 0)
	//		{
	//			kolejnosc++;
	//			if(kolejnosc >= tmp.size()) kolejnosc = 0;
	//			selected = tmp[kolejnosc];
	//			drag = true;
	//			lx = GetX();
	//			ly = GetY();
	//			view->SetTitle("SELECTED OBJECT");
	//			view->SetObject(*selected);
	//			//lw = glfwGetMouseWheel();
	//		}
	//		else
	//		{
	//			selected = nullptr;
	//			view->SetTitle("VIEWER");
	//			view->SetObject(nullptr);
	//		}
	//	}
	//	else
	//	{
	//		float dx = GetX() - lx;
	//		float dy = GetY() - ly;
	//		
	//		//DRAG&DROP
	//		int w = engine->GetCurrentMap()->getBGImage()->width, sw = screen->getWidth();
	//		int h = engine->GetCurrentMap()->getBGImage()->height, sh = screen->getHeight();
	//		float zoomW = engine->GetZoom();
	//		float zoomH = (sh * zoomW)/sw;

	//		selected->_Ptr->Set(selected->_Ptr->GetX() + dx*zoomW/(sw*w),selected->_Ptr->GetY() - dy*zoomH/(sh*h));
	//		lx = GetX();
	//		ly = GetY();
	//	}
	//}
	//if(GetButtState(0) == KEY_PRESS)
	//{
	//	drag = false;
	//}
	/////////////////////////////////////USUN OBIEKT LOKALNY/////////////////
	if(isDown(GLFW_KEY_DEL) && selected.size() > 0)
	{
		vector<link<Object>>& obj = engine->GetCurrentMap()->GetObjectVecRef();
		std::sort(selected.begin(),selected.end());
		for(int i = selected.size() - 1; i >= 0; i--)
		{
			delete obj[selected[i]]; //usun animacje
			engine->GetCurrentMap()->GetObjectVecRef().erase(engine->GetCurrentMap()->GetObjectVecRef().begin() + selected[i]); 
		}
		selected.clear();
	}
	//////////////////////////////////  CTRL + C && CTRL + V ////////////////////////
	if(isDown(GLFW_KEY_LCTRL) && isDown('C'))
	{
		storage = selected;
	}
	if(isDown(GLFW_KEY_LCTRL) && isDown('V',true))
	{
		vector<link<Object>>& obj = engine->GetCurrentMap()->GetObjectVecRef();

		for(unsigned int i = 0; i < storage.size(); i++)
		{

			link<Object> o = link<Object>(new Object(*obj[storage[i]]),obj[storage[i]].Name,obj[storage[i]].Id);
			o->Set(o->GetX() + 15, o->GetY() + 15);
			obj.push_back(o);
		}
		//storage.clear();
	}
	/////////////////////////////////////////////////////////////////
	if(isDown(GLFW_KEY_LCTRL) && isDown('F'))
	{
		for(unsigned int i = 0; i < selected.size(); i++)
		{
			link<Object> o = engine->GetCurrentMap()->GetObjectVecRef()[selected[i]];
			engine->GetCurrentMap()->GetObjectVecRef().erase(engine->GetCurrentMap()->GetObjectVecRef().begin() + selected[i]);
			engine->GetCurrentMap()->GetObjectVecRef().push_back(o);
		}
		selected.clear();
	}
	//////////////////////////////////NOWY OBIEKT////////////////////
	if(isDown(GLFW_KEY_LCTRL) && isDown('N') && engine->HasMap())
	{
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = new link<Object>();
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OBJECT_WINDOWS,tmp));
		return;
	}
	////////////////////////////////EDYCJA OBIEKYU LOKALNEGO MAPY///////////////////////////
	if(isDown(GLFW_KEY_LCTRL) && isDown('E') && selected.size() == 1 )
	{
		//skopiowac obiekt TODO
		newObject = link<Object>(new Object(*engine->GetCurrentMap()->GetObjectVecRef()[selected[0]]),engine->GetCurrentMap()->GetObjectVecRef()[selected[0]].Name,engine->GetCurrentMap()->GetObjectVecRef()[selected[0]].Id);
		//for(unsigned i=0; i<selected[0]->_Ptr->GetAnimVecRef().size(); i++)
		//	newObject->GetAnimVecRef().push_back(new Animation(*selected[0]->_Ptr->GetAnimVecRef().at(i)));
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = &newObject;
		eventQueue.push_back(new SetAllActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OBJECT_WINDOWS,tmp));
		editWindow = true;
		return;
	}
	if(editWindow)
	{
		editWindow = false;
		if(newObject != nullptr)
		{
			//odklonowac TODO
			//for(unsigned i=0; i<selected[0]->_Ptr->GetAnimVecRef().size(); i++)
			//	delete selected[0]->_Ptr->GetAnimVecRef()[i]._Ptr;
			delete engine->GetCurrentMap()->GetObjectVecRef()[selected[0]];
			engine->GetCurrentMap()->GetObjectVecRef()[selected[0]] = newObject;
		}
	}
	//////////////////////////EXISTING OBJECT//////////////////
	if(isDown(GLFW_KEY_LCTRL) && isDown('E') && selected.size() == 0 )
	{
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OLD_OBJECT_WINDOW));
		return;
	}
	///////////////////////////NEW MAP/////////////////////////
	if(((isDown(GLFW_KEY_LCTRL) && isDown(GLFW_KEY_LSHIFT) && isDown('N')) || newMapButton->pressed))
	{
		newMapButton->pressed = false;
		if(!engine->HasMap())
		{
			newMapWindow = true;
			vector<void*>* tmp = new vector<void*>(1);
			newMap = link<Map>(nullptr);
			(*tmp)[0] = &newMap;
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::NEW_MAP_WINDOW,tmp));
			return;
		}
		else
		{
			saveForNew = true;
			vector<void*>* tmp = new vector<void*>(1);
			(*tmp)[0] = &saveResult;
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::SAVE_WINDOW,tmp));
			return;
		}
	}
	if(saveForNew) 
	{
		saveForNew = false;
		if(saveResult)
		{
			newMapWindow = true;
			vector<void*>* tmp = new vector<void*>(1);
			newMap = link<Map>(nullptr);
			(*tmp)[0] = &newMap;
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::NEW_MAP_WINDOW,tmp));
			return;
		}
	}
	if(newMapWindow)
	{
		newMapWindow = false;
		if(newMap._Ptr != nullptr)
		{
			engine->SetCurrentMap(newMap);
			engine->ResetZoom();
		}
	}

	///////////////////////////OLD MAP/////////////////////////
	if(((isDown(GLFW_KEY_LCTRL) && isDown('O')) || oldMapButton->pressed))
	{
		oldMapButton->pressed = false;
		if(!engine->HasMap())
		{
			oldMapWindow = true;
			vector<void*>* tmp = new vector<void*>(1);
			(*tmp)[0] = &mapId;
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OLD_MAP_WINDOW,tmp));
			return;
		}
		else
		{
			saveForOld = true;
			vector<void*>* tmp = new vector<void*>(1);
			(*tmp)[0] = &saveResult;
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::SAVE_WINDOW,tmp));
			return;
		}
	}
	if(saveForOld) 
	{
		saveForOld = false;
		if(saveResult)
		{
			oldMapWindow = true;
			vector<void*>* tmp = new vector<void*>(1);
			(*tmp)[0] = &mapId;
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
			eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OLD_MAP_WINDOW,tmp));
			return;
		}
	}
	if(oldMapWindow)
	{
		oldMapWindow = false;
		if(mapId != -1)
		{
			engine->SetCurrentMap(gom->CopyMapByID(mapId));
			engine->ResetZoom();
		}
	}	
	////////////////////////////SAVE//////////////////////////////////////////////
	if(((isDown(GLFW_KEY_LCTRL) && isDown(GLFW_KEY_LSHIFT) && isDown('S')) || saveButton->pressed) && engine->HasMap())
	{
		saveButton->pressed = false;
		int id = engine->GetCurrentMap().Id;
		if(id != -1)// Edytowalismy istniejaca mape
		{
			std::link<Map>& map = const_cast<std::link<Map>&>(gom->GetMapByID(id));
			gom->RemoveMapByID(id);
			map = engine->GetCurrentMap();
			engine->SetCurrentMap(gom->CopyMapByID(id));
		}
		else //To byla noawa mapa
		{
			engine->SetCurrentMap(gom->CopyMapByID(gom->AddNewMap(engine->GetCurrentMap(),engine->GetCurrentMap().Name).Id));		
		}

		gom->SaveAllTextures("Content\\textures.xml");
		gom->SaveAllObjects("Content\\objects.xml");
		gom->SaveAllCreatures("Content\\creatures.xml");
		gom->SaveAllItems("Content\\items.xml");
		gom->SaveAllMaps("Content\\maps.xml");
	}
	///////////////////////////SAVE AS////////////////////////////////////////////
	if(((isDown(GLFW_KEY_LCTRL) && isDown('S')) || saveAsButton->pressed) && engine->HasMap())
	{
		saveAsButton->pressed = false;
		vector<void*>* tmp = new vector<void*>(2);
		(*tmp)[0] = new string("Podaj nazwe mapy");
		(*tmp)[1] = &nameFromAsk;
		saveAsWindow = true;
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::ASK_WINDOW,tmp));
		return;
	}
	if(saveAsWindow)
	{
		saveAsWindow = false;
		engine->SetCurrentMap(gom->AddNewMap(engine->GetCurrentMap(),nameFromAsk));
		gom->SaveAllTextures("Content\\textures.xml");
		gom->SaveAllObjects("Content\\objects.xml");
		gom->SaveAllCreatures("Content\\creatures.xml");
		gom->SaveAllItems("Content\\items.xml");
		gom->SaveAllMaps("Content\\maps.xml");
	}
	//////////////////////////TEXTURE BROWSER////////////////////////////////////
	if(texturesButton->pressed)
	{
		texturesButton->pressed = false;
		vector<void*>* tmp = new vector<void*>(1);
		(*tmp)[0] = new int(-133);
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_FALSE));
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::OLD_TEXTURE_WINDOW,tmp));
		return;
	}
	/////////////////////////////////////////////////////////////////////////////
	if(isDown(ESC))
	{
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new NewWindowEvent(WINDOWS_TYPE::MAIN_MENU_WINDOWS));
	}
	/////////////////////////////////////////////////////////////////////////////
	if(zoomInButton->pressed || isDown(GLFW_KEY_KP_ADD,true))
	{
		zoomInButton->pressed = false;
		engine->Zoom(1);
	}
	if(zoomOutButton->pressed || isDown(GLFW_KEY_KP_SUBTRACT,true))
	{
		zoomOutButton->pressed = false;
		engine->Zoom(-1);
	}
	if(zoom100Button->pressed || isDown(GLFW_KEY_SPACE,true))
	{
		zoom100Button->pressed = false;
		engine->ResetZoom();
	}
	/////////////////////////////////////
	if(playButton->pressed)
	{
		playButton->pressed = false;
		isPlaying = true;
	}
	else if(stopButton->pressed)
	{
		stopButton->pressed = false;
		isPlaying = false;
	}
	else if(resetButton->pressed)
	{
		resetButton->pressed = false;
		isPlaying = false;
		for(unsigned i=0; i<engine->GetCurrentMap()->GetObjectVecRef().size(); i++)
		{
			engine->GetCurrentMap()->GetObjectVecRef().at(i)->GetCurrentAnim()->Reset();
		}
	}

	if(gridButton->pressed)
	{
		gridButton->pressed = false;
		gridVisible = !gridVisible;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////   MANAGERS   /////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(objectManagerButton->pressed)
	{
		objectManagerButton->pressed = false;
		manager->SwitchVisible();
	}

	if(objectListButton->pressed)
	{
		objectListButton->pressed = false;
		if(engine->HasMap()) existing->SwitchVisible();
	}

	if(viewButton->pressed || isPressed('O'))
	{
		viewButton->pressed = false;
		view->SwitchVisible();
	}

	if(manager->IndexChange())
	{
		view->SetObject(gom->GetObjectByID(manager->GetSelectedIndex()));
		view->SetTitle("NEW OBJECT");
	}

	if(terrainButton->pressed)
	{
		terrainButton->pressed = false;
		if(engine->HasMap()) terrain->SwitchVisible();
	}


}

void EdytorWindow::Draw()
{
	if(!active) glColor4f(1,1,1,0.5f);
	if(engine->HasMap())
	{
		engine->DrawMap();
		if(gridVisible)
		{
			glColor3f(0.8,0.8,0.5);
			engine->DrawGrid();
		}
		for(unsigned int i = 0; i < engine->GetCurrentMap()->GetObjectVecRef().size(); i++)
		{
			link<Object> o = engine->GetCurrentMap()->GetObjectVecRef()[i];
			engine->DrawObject(o);
			glColor3f(0.8,0.8,0.8);
			for(unsigned int j = 0; j < selected.size(); j++)
				if(i == selected[j]) { glColor3f(1,0.80f,0.05f); break; }
			engine->DrawFrame(o);
			engine->DrawPolygon(o);
		}
	}

	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,bar->texID);
	glBegin(GL_QUADS);
		for(int i = 0; i < w; i+=545)
		{
			glTexCoord2f(0,0); glVertex3f(i,h-52,0);
			glTexCoord2f(1,0); glVertex3f(i+545,h-52,0);
			glTexCoord2f(1,1); glVertex3f(i+545,h,0);
			glTexCoord2f(0,1); glVertex3f(i,h,0);
		}
	glEnd();

	Controlka::glPrint(screen->getWidth() - 100, screen->getHeight() - 28, 0.8f, ("zoom: " + etos((int)(engine->GetZoom()*100)) + "%%").c_str());

	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,bar2->texID);
	glBegin(GL_QUADS);
		for(int i = 0; i < w; i+=545)
		{
			glTexCoord2f(0,0); glVertex3f(i,15,0);
			glTexCoord2f(1,0); glVertex3f(i+545,15,0);
			glTexCoord2f(1,1); glVertex3f(i+545,-2,0);
			glTexCoord2f(0,1); glVertex3f(i,-2,0);
		}
	glEnd();

	if(!engine->HasMap())
	{
		saveButton->ForceState(2);
		saveAsButton->ForceState(2);
		properties->ForceState(2);
		mapSettings->ForceState(2);
		scriptEditor->ForceState(2);
		objectListButton->ForceState(2);
		viewButton->ForceState(2);
		terrainButton->ForceState(2);
		playButton->ForceState(2);
		stopButton->ForceState(2);
		resetButton->ForceState(2);
	}

	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();

	if(!engine->HasMap())
	{
		saveButton->ForceState(0);
		saveAsButton->ForceState(0);
		properties->ForceState(0);
		mapSettings->ForceState(0);
		scriptEditor->ForceState(0);
		objectListButton->ForceState(0);
		viewButton->ForceState(0);
		terrainButton->ForceState(0);
		playButton->ForceState(0);
		stopButton->ForceState(0);
		resetButton->ForceState(0);
	}

	manager->Draw();
	view->Draw();
	existing->Draw();
	terrain->Draw();

	if(!active) 
	{
		glDisable(GL_TEXTURE_2D);
		glColor4f(0,0,0,0.5);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(w,0,0);
			glVertex3f(w,h,0);
			glVertex3f(0,h,0);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}
}


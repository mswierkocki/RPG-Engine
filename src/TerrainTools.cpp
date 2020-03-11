#include "TerrainTools.h"

using namespace Input;


TerrainTools::TerrainTools(Engine* engine):engine(engine)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(11);
	tmp[0] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[1] = link<Controlka*>((Controlka**)&lButton,"lButton");
	tmp[2] = link<Controlka*>((Controlka**)&rButton,"rButton");
	tmp[3] = link<Controlka*>((Controlka**)&brushButton,"brushButton");
	tmp[4] = link<Controlka*>((Controlka**)&eraseButton,"eraseButton");
	tmp[5] = link<Controlka*>((Controlka**)&cutButton,"cutButton");
	tmp[6] = link<Controlka*>((Controlka**)&baseButton,"baseButton");
	tmp[7] = link<Controlka*>((Controlka**)&field,"field");
	tmp[8] = link<Controlka*>((Controlka**)&x1Button,"x1Button");
	tmp[9] = link<Controlka*>((Controlka**)&x2Button,"x2Button");
	tmp[10] = link<Controlka*>((Controlka**)&x3Button,"x3Button");

	LoadContent("Windows\\TerrainTools.xml",tmp);

	base = 0;
	size = 1;
	maxBase = Map::GetBaseCount();
	maxRandom = Map::GetBaseRandom();
	isBase = true;
	isCut = isBrush = isErase = false;
}

void TerrainTools::SetVisible()
{
	visible = true;
}

void TerrainTools::SetInVisible()
{
	visible = false;
}

void TerrainTools::SwitchVisible()
{
	if(visible)
		SetInVisible();
	else
		SetVisible();
}

void TerrainTools::Set(unsigned int x, unsigned int y)
{
	if(isBase)
	{
		int bbase = (base == maxBase-1)?124:base;
		if(size == 1)
		{
			engine->GetCurrentMap()->Get(x,y).SetBase(bbase,maxRandom);
		}
		else if(size == 2)
		{
			engine->GetCurrentMap()->Get(x,y).SetBase(bbase,maxRandom);
			if(x < engine->GetCurrentMap()->GetHeight() - 1 && y < engine->GetCurrentMap()->GetHeight())
			{
				engine->GetCurrentMap()->Get(x+1,y).SetBase(bbase,maxRandom);
				engine->GetCurrentMap()->Get(x+1,y+1).SetBase(bbase,maxRandom);
				engine->GetCurrentMap()->Get(x,y+1).SetBase(bbase,maxRandom);
			}
		}
		else if(size == 3)
		{
			engine->GetCurrentMap()->Get(x,y).SetBase(bbase,maxRandom);
			if(x < engine->GetCurrentMap()->GetHeight() - 1 && y < engine->GetCurrentMap()->GetHeight() && x > 0 && y > 0)
			{
				engine->GetCurrentMap()->Get(x-1,y+1).SetBase(bbase,maxRandom);
				engine->GetCurrentMap()->Get(x,y+1).SetBase(bbase,maxRandom);
				engine->GetCurrentMap()->Get(x+1,y+1).SetBase(bbase,maxRandom);

				engine->GetCurrentMap()->Get(x-1,y).SetBase(bbase,maxRandom);
				engine->GetCurrentMap()->Get(x+1,y).SetBase(bbase,maxRandom);

				engine->GetCurrentMap()->Get(x-1,y-1).SetBase(bbase,maxRandom);
				engine->GetCurrentMap()->Get(x,y-1).SetBase(bbase,maxRandom);
				engine->GetCurrentMap()->Get(x+1,y-1).SetBase(bbase,maxRandom);
			}
		}
	}
	else if(isBrush)
	{
		if(size == 1)
		{
			for(int i = 0; i < 1; i++)
				engine->GetCurrentMap()->Get(x,y).SetType(base,maxRandom);

			for(int i = 0; i < 9; i++)
				engine->GetCurrentMap()->Refresh(x - 1 + (i%3), y - 1 + (i/3));
		}
		else if(size == 2)
		{
			for(int i = 0; i < 4; i++)
				engine->GetCurrentMap()->Get(x+(i%2),y+(i/2)).SetType(base,maxRandom);

			for(int i = 0; i < 16; i++)
				engine->GetCurrentMap()->Refresh(x - 1 + (i%4), y - 1 + (i/4));
		}
		else if(size == 3)
		{
			for(int i = 0; i < 9; i++)
				engine->GetCurrentMap()->Get(x-1+(i%3),y-1+(i/3)).SetType(base,maxRandom);

			for(int i = 0; i < 25; i++)
				engine->GetCurrentMap()->Refresh(x - 2 + (i%5), y - 2 + (i/5));
		}
	}
	else if(isCut)
	{
		if(size == 1)
		{
			engine->GetCurrentMap()->Get(x,y).type = 124;
		}
		else if(size == 2)
		{
			for(int i = 0; i < 4; i++)
				engine->GetCurrentMap()->Get(x + (i%2), y + (i/2)).type = 124;
		}
		else if(size == 3)
		{
			for(int i = 0; i < 9; i++)
				engine->GetCurrentMap()->Get(x - 1 + (i%3), y - 1 + (i/3)).type = 124;
		}
	}
	else if(isErase)
	{
		if(size == 1)
		{
			for(int i = 0; i < 1; i++)
				engine->GetCurrentMap()->Get(x,y).type = 124;
			for(int i = 0; i < 9; i++)
				engine->GetCurrentMap()->Refresh(x - 1 + (i%3), y - 1 + (i/3));
		}
		else if(size == 2)
		{
			for(int i = 0; i < 4; i++)
				engine->GetCurrentMap()->Get(x + (i%2), y + (i/2)).type = 124;
			for(int i = 0; i < 16; i++)
				engine->GetCurrentMap()->Refresh(x - 1 + (i%4), y - 1 + (i/4));
		}
		else if(size == 3)
		{
			for(int i = 0; i < 9; i++)
				engine->GetCurrentMap()->Get(x - 1 + (i%3), y - 1 + (i/3)).type = 124;
			for(int i = 0; i < 25; i++)
				engine->GetCurrentMap()->Refresh(x - 2 + (i%5), y - 2 + (i/5));
		}
	}
}

void TerrainTools::Update(double deltaTime)
{
	if(!visible) return;

	int mx = GetX();
	int my = screen->getHeight() - GetY();
	Pointf off = getOffset();
	if(mx > off.x && mx < off.x + w && my > off.y && my < off.y + h )
	{
		InputManager::RestoreMouse();
	}

	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(x1Button->pressed)
	{
		x1Button->pressed = false;
		size = 1;
	}
	if(x2Button->pressed)
	{
		x2Button->pressed = false;
		size = 2;
	}
	if(x3Button->pressed)
	{
		x3Button->pressed = false;
		size = 3;
	}
	if(baseButton->pressed)
	{
		baseButton->pressed = false;
		isBase = true;
		isBrush = isCut = isErase = false;;
	}
	if(brushButton->pressed)
	{
		brushButton->pressed = false;
		isBrush = true;
		isBase = isCut = isErase = false;
	}
	if(eraseButton->pressed)
	{
		eraseButton->pressed = false;
		isErase = true;
		isBrush = isBase = isCut = false;
	}
	if(cutButton->pressed)
	{
		cutButton->pressed = false;
		isCut = true;
		isBrush = isBase = isErase = false;
	}

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
	if(backButton->pressed)
	{
		backButton->pressed = false;
		visible = false;
	}
	if(mx > off.x && mx < off.x + w && my > off.y && my < off.y + h )
	{
		InputManager::ConsumeMouse();
	}

}

void TerrainTools::Draw()
{
	if(!visible) return;

	if(size == 1) x1Button->ForceState(2);
	else if(size == 2) x2Button->ForceState(2);
	else if(size == 3) x3Button->ForceState(2);

	if(isBase)       baseButton->ForceState(2);
	else if(isBrush) brushButton->ForceState(2);
	else if(isErase) eraseButton->ForceState(2);
	else if(isCut)   cutButton->ForceState(2);


	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();

	if(size == 1) x1Button->ForceState(0);
	else if(size == 2) x2Button->ForceState(0);
	else if(size == 3) x3Button->ForceState(0);

	if(isBase)       baseButton->ForceState(0);
	else if(isBrush) brushButton->ForceState(0);
	else if(isErase) eraseButton->ForceState(0);
	else if(isCut)   cutButton->ForceState(0);

	Pointf off, size;
	field->CountField(TILESIZE,TILESIZE,off,size);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,Map::GetBase()->texID);
	float x = base / (float)maxBase;
	float dx = 1.0f / (float)maxBase;
	float dy = 1.0f / (float)maxRandom; 
	glBegin(GL_QUADS);
		glTexCoord2f(x,1-dy);    glVertex2f(off.x       , off.y);
		glTexCoord2f(x+dx,1-dy); glVertex2f(off.x+size.x, off.y);
		glTexCoord2f(x+dx,1); glVertex2f(off.x+size.x, off.y+size.y);
		glTexCoord2f(x,1);    glVertex2f(off.x       , off.y+size.y);
	glEnd();
}
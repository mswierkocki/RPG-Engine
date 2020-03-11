#include "link.hpp"
#include "Engine.h"

using namespace Input;


Engine::Engine(GameObjectManager *gom)
{
	this->gom = gom;
	zoom = 1;
	state = 6;
	mapCoords.x = 0;
	mapCoords.y = 0;
	polygonsEnabled = false;
	framesEnabled = false;
}

void Engine::Draw()
{
}

void Engine::Update(double deltaTime)
{
	if(currentMap == nullptr) return;
	for(unsigned int i = 0; i < currentMap->GetObjectVecRef().size(); i++)
	{
		currentMap->GetObjectVecRef()[i]->Update(deltaTime);
	}
}


void Engine::Zoom(int delta)
{
	if(currentMap == nullptr) return;
	float w = currentMap->GetW(), sw = screen->getWidth();
	float h = currentMap->GetH(), sh = screen->getHeight();

	//hard zoom component varies from 16,6% (state=1) to 400% (state=10)
	int i = state + delta;

	float z = (i>6?i-4.0f:i/3.0f)/2.0f; //makes strange range 16,6% to 400% plausible

	//if(sh/(zoom * z) < h && sw/(zoom * z) < w)
	if(i >= 1 && i <= 12 && sh / z < h && sw / z < w)
	{
		state += delta;
		
		//mapCoords.x += sw/2*(1/zoom-1/z);
		//mapCoords.y += sh/2*(1/zoom-1/z);

		mapCoords.x += (Input::GetX())*(1/zoom-1/z);
		mapCoords.y += (sh-Input::GetY())*(1/zoom-1/z);

		zoom = z;
		
		if(mapCoords.x < 0) mapCoords.x = 0;
		if(mapCoords.y < 0) mapCoords.y = 0;

		if(mapCoords.x + sw/zoom > w) mapCoords.x = w - sw/zoom;
		if(mapCoords.y + sh/zoom > h) mapCoords.y = h - sh/zoom;
	}
}

void Engine::MoveMap(Pointf mov)
{
	if(currentMap == nullptr) return;

	float w = currentMap->GetW(), sw = screen->getWidth();
	float h = currentMap->GetH(), sh = screen->getHeight();

	mapCoords.x += mov.x; 
	mapCoords.y += mov.y;
	if(mapCoords.x < 0) mapCoords.x = 0;
	if(mapCoords.y < 0) mapCoords.y = 0;

	if(mapCoords.x + sw/zoom > w) mapCoords.x = w - sw/zoom;
	if(mapCoords.y + sh/zoom > h) mapCoords.y = h - sh/zoom;
}

void Engine::SetMapPos(Pointf mov)
{
	float w = currentMap->GetW(), sw = screen->getWidth();
	float h = currentMap->GetH(), sh = screen->getHeight();

	mapCoords = mov;
	if(mapCoords.x < 0) mapCoords.x = 0;
	if(mapCoords.y < 0) mapCoords.y = 0;

	if(mapCoords.x + sw/zoom > w) mapCoords.x = w - sw/zoom;
	if(mapCoords.y + sh/zoom > h) mapCoords.y = h - sh/zoom;
}

void Engine::DrawMap()
{
	if(currentMap == nullptr) return;

	Pointf offset;
	int w = currentMap->GetW(), sw = screen->getWidth();
	int h = currentMap->GetH(), sh = screen->getHeight();

	int startX = (int)mapCoords.x / TILESIZE;
	int startY = (int)mapCoords.y / TILESIZE;

	int stopX = ( (int)(mapCoords.x + sw/zoom) / TILESIZE ) + 2;
	int stopY = ( (int)(mapCoords.y + sh/zoom) / TILESIZE ) + 1;


	glBindTexture(GL_TEXTURE_2D,currentMap->GetBase()->texID);

	float tw = currentMap->GetBase()->width;
	float th = currentMap->GetBase()->height;
	int base;
	int baseNr;
	int type;
	int nr;
	int typeNr;
	float xx,dxx,yy,dyy;

	
	glColor3f(1,1,1);
	int ex = (startX*TILESIZE - mapCoords.x)*zoom;
	int skok = (int)(TILESIZE * zoom);

	/////////////////////////////////////////BASE - PODKLAD //////////////
	for(int x = startX; x <stopX; x++)
	{
		for(int y = startY; y < stopY; y++)
		{
			base = currentMap->Get(x,y).base;
			baseNr = currentMap->Get(x,y).baseNr;
			if(base == 124) continue;
			xx = base / (tw / TILESIZE) + 0.001;
			dxx =  TILESIZE / tw - 0.002;
			yy = baseNr / (th / TILESIZE);
			dyy = TILESIZE / th;
			glBegin(GL_QUADS);
				glTexCoord2f(xx      , yy      ); glVertex3f(ex       , (y*TILESIZE - mapCoords.y)*zoom,0);
				glTexCoord2f(xx + dxx, yy      ); glVertex3f(ex + skok, (y*TILESIZE - mapCoords.y)*zoom,0);
				glTexCoord2f(xx + dxx, yy + dyy); glVertex3f(ex + skok, ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
				glTexCoord2f(xx      , yy + dyy); glVertex3f(ex       , ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
			glEnd();
		}
		ex += skok;
	}



	tw = currentMap->GetParts()->width;
	th = currentMap->GetParts()->height;
	ex = (startX*TILESIZE - mapCoords.x)*zoom;
	skok = (int)(TILESIZE * zoom);

	////////////////////////////////////////////MASKA/////////////////////////

	glDisable(GL_DEPTH_TEST);
	float tww = currentMap->GetBase()->width;
	float thh = currentMap->GetBase()->height;

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, currentMap->GetParts()->texID);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
 
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, currentMap->GetBase()->texID); 
	glEnable(GL_TEXTURE_2D);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_INCR);


	//glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
	glColor3f(1,1,1);
	for(int x = startX; x <stopX; x++)
	{
		for(int y = startY; y < stopY; y++)
		{
			type = currentMap->Get(x,y).type;
			nr = currentMap->Get(x,y).nr;
			typeNr = currentMap->Get(x,y).typeNr;
			if(type == 124) continue;

			xx  = type / (tww / TILESIZE) + 0.001;
			dxx = TILESIZE / tww - 0.002;
			yy  = typeNr / (thh / TILESIZE);
			dyy = TILESIZE / thh;

			glBegin(GL_QUADS);
				glMultiTexCoord2fARB(GL_TEXTURE0_ARB,nr / (tw / TILESIZE)                , 0);
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB,xx                   , yy);
				glVertex3f(ex, (y*TILESIZE - mapCoords.y)*zoom, 0);

				glMultiTexCoord2fARB(GL_TEXTURE0_ARB,nr / (tw / TILESIZE) + TILESIZE / tw, 0);
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB,xx + dxx, yy);
				glVertex3f(ex + skok, (y*TILESIZE - mapCoords.y)*zoom    ,0);

				glMultiTexCoord2fARB(GL_TEXTURE0_ARB,nr / (tw / TILESIZE) + TILESIZE / tw, 1);
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB,xx + dxx, yy+dyy);
				glVertex3f(ex + skok, ((y+1)*TILESIZE - mapCoords.y)*zoom,0);

				glMultiTexCoord2fARB(GL_TEXTURE0_ARB,nr / (tw / TILESIZE)                , 1);
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB,xx      , yy+dyy);
				glVertex3f(ex       , ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
			glEnd();
		}
		ex += skok;
	}

	glActiveTextureARB(GL_TEXTURE1); 
	glDisable(GL_TEXTURE_2D); 

	glActiveTextureARB(GL_TEXTURE0); 
	//glDisable(GL_TEXTURE_2D);

	//glEnable(GL_TEXTURE_2D);



	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//
	//tw = currentMap->GetParts()->width;
	//th = currentMap->GetParts()->height;
	//ex = (startX*TILESIZE - mapCoords.x)*zoom;
	//skok = (int)(TILESIZE * zoom);

	////////////////////////////////////////////////MASKA/////////////////////////

	//glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	//
	////glBlendFunc(GL_ONE, GL_ZERO);
	////glDisable(GL_BLEND);
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
	////glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ZERO);
	////glBlendFunc(GL_DST_COLOR,GL_ZERO);      //NE HE

	//glBindTexture(GL_TEXTURE_2D,currentMap->GetParts()->texID);
	//glColor3f(1,1,1);
	//for(int x = startX; x <stopX; x++)
	//{
	//	for(int y = startY; y < stopY; y++)
	//	{
	//		type = currentMap->Get(x,y).type;
	//		nr = currentMap->Get(x,y).nr;
	//		if(type == 124) continue;
	//		glBegin(GL_QUADS);
	//			glTexCoord2f(0, 0);  glVertex3f(ex       , (y*TILESIZE - mapCoords.y)*zoom    ,0);
	//			glTexCoord2f(1, 0);  glVertex3f(ex + skok, (y*TILESIZE - mapCoords.y)*zoom    ,0);
	//			glTexCoord2f(1, 1);  glVertex3f(ex + skok, ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
	//			glTexCoord2f(0, 1);  glVertex3f(ex       , ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
	//		glEnd();
	//		//glBegin(GL_QUADS);
	//		//	glTexCoord2f(nr / (tw / TILESIZE)                , 0);  glVertex3f(ex       , (y*TILESIZE - mapCoords.y)*zoom    ,0);
	//		//	glTexCoord2f(nr / (tw / TILESIZE) + TILESIZE / tw, 0);  glVertex3f(ex + skok, (y*TILESIZE - mapCoords.y)*zoom    ,0);
	//		//	glTexCoord2f(nr / (tw / TILESIZE) + TILESIZE / tw, 1);  glVertex3f(ex + skok, ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
	//		//	glTexCoord2f(nr / (tw / TILESIZE)                , 1);  glVertex3f(ex       , ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
	//		//glEnd();
	//	}
	//	ex += skok;
	//}

	//////////////////////////////////////////// TAILS //////////////////
	//tw = currentMap->GetBase()->width;
	//th = currentMap->GetBase()->height;
	//ex = (startX*TILESIZE - mapCoords.x)*zoom;
	//skok = (int)(TILESIZE * zoom);

	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//glEnable(GL_BLEND);
	//glBlendEquation(GL_FUNC_ADD);
	//glBlendFuncSeparate(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA, GL_ZERO, GL_ONE);
	////glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ZERO);
	////glBindTexture(GL_TEXTURE_2D,currentMap->GetBase()->texID);


	//for(int x = startX; x <stopX; x++)
	//{
	//	for(int y = startY; y < stopY; y++)
	//	{
	//		type = currentMap->Get(x,y).type;
	//		if(type == 124) continue;
	//		xx = type / (tw / TILESIZE) + 0.001;
	//		dxx =  TILESIZE / tw - 0.002;
	//		dyy = TILESIZE / th;
	//		glBegin(GL_QUADS);
	//			glTexCoord2f(xx      , 1 - dyy); glVertex3f(ex       , (y*TILESIZE - mapCoords.y)*zoom,0);
	//			glTexCoord2f(xx + dxx, 1 - dyy); glVertex3f(ex + skok, (y*TILESIZE - mapCoords.y)*zoom,0);
	//			glTexCoord2f(xx + dxx, 1);       glVertex3f(ex + skok, ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
	//			glTexCoord2f(xx      , 1);       glVertex3f(ex       , ((y+1)*TILESIZE - mapCoords.y)*zoom,0);
	//		glEnd();
	//	}
	//	ex += skok;
	//}
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Engine::DrawGrid()
{
	if(currentMap == nullptr) return;

	int sw = screen->getWidth();
	int sh = screen->getHeight();

	int startX = (int)mapCoords.x / TILESIZE;
	int startY = (int)mapCoords.y / TILESIZE;

	int stopX = ( (int)(mapCoords.x + sw/zoom) / TILESIZE ) + 2;
	int stopY = ( (int)(mapCoords.y + sh/zoom) / TILESIZE ) + 1;
	
	glColor3f(1,1,1);
	int ex = (startX*TILESIZE - mapCoords.x)*zoom;
	int ey = (startY*TILESIZE - mapCoords.y)*zoom;
	int skok = (int)(TILESIZE * zoom);

	/////////////////////////////////////////SIAKKA//////////////
	glDisable(GL_TEXTURE_2D);
	for(int x = startX; x <stopX; x++)
	{
		glBegin(GL_LINES);
			glVertex3f(ex, 0, 0);
			glVertex3f(ex, sh,0);
		glEnd();
		ex += skok;
	}
	for(int y = startY; y < stopY; y++)
	{
		glBegin(GL_LINES);
			glVertex3f(0, ey, 0);
			glVertex3f(sw, ey, 0);
		glEnd();
		ey += skok;
	}
	glEnable(GL_TEXTURE_2D);
}

void Engine::DrawObjects()
{
	if(currentMap == nullptr) return;

	vector<link<Object>>& objs = currentMap->GetObjectVecRef();

	for(unsigned i=0; i<objs.size(); i++)
	{
		float scale = objs[i]->GetScale();

		float x = (objs[i]->GetX() - mapCoords.x)* zoom;
		float y = (objs[i]->GetY() - mapCoords.y) * zoom;
		float dx = (objs[i]->GetCurrentAnim()->GetFrameWidth() * scale) * zoom;
		float dy = (objs[i]->GetCurrentAnim()->GetFrameHeight() * scale) * zoom;

		objs[i]->GetCurrentAnim()->Draw(x,y,dx,dy);

		if(polygonsEnabled)
		{

		}
	}
}

void Engine::DrawObject(Object* o)
{
	if(currentMap == nullptr) return;

	float scale = o->GetScale();
	float x = (o->GetX() - mapCoords.x)* zoom;
	float y = (o->GetY() - mapCoords.y) * zoom;
	float dx = (o->GetCurrentAnim()->GetFrameWidth() * scale) * zoom;
	float dy = (o->GetCurrentAnim()->GetFrameHeight() * scale) * zoom;
	 o->GetCurrentAnim()->Draw(x,y,dx,dy);
}

void Engine::DrawFrame(Object* o)
{
	if(currentMap == nullptr) return;

	float scale = o->GetScale();
	float x = (o->GetX() - mapCoords.x)* zoom;
	float y = (o->GetY() - mapCoords.y) * zoom;
	float dx = (o->GetCurrentAnim()->GetFrameWidth() * scale) * zoom;
	float dy = (o->GetCurrentAnim()->GetFrameHeight() * scale) * zoom;

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINE_STRIP);
		glVertex3f(x,y,0);
		glVertex3f(x+dx,y,0);
		glVertex3f(x+dx,y+dy,0);
		glVertex3f(x,y+dy,0);
		glVertex3f(x,y,0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void Engine::DrawPolygon(Object* o)
{
	if(currentMap == nullptr) return;
}

vector<link<Object>*> Engine::GetObjectsUnderMouse()
{
	vector<link<Object>*> tmp; if(currentMap == nullptr) return tmp;
	vector<link<Object>>& objs = currentMap->GetObjectVecRef();

	for(unsigned i=0; i<objs.size(); i++)
	{
		float scale = objs[i]->GetScale();
		float x = (objs[i]->GetX() - mapCoords.x)* zoom;
		float y = (objs[i]->GetY() - mapCoords.y) * zoom;
		float dx = (objs[i]->GetCurrentAnim()->GetFrameWidth() * scale) * zoom;
		float dy = (objs[i]->GetCurrentAnim()->GetFrameHeight() * scale) * zoom;
		float mx = GetX();
		float my = screen->getHeight() - GetY();
		
		if (mx > x && mx < x+dx && my > y && my < y+dy) tmp.push_back(&objs[i]); 
	}
	return tmp;
}

vector<int> Engine::GetObjectsIdUnderMouse()
{
	vector<int> tmp; if(currentMap == nullptr) return tmp;
	vector<link<Object>>& objs = currentMap->GetObjectVecRef();

	for(unsigned i=0; i<objs.size(); i++)
	{
		float scale = objs[i]->GetScale();
		float x = (objs[i]->GetX() - mapCoords.x)* zoom;
		float y = (objs[i]->GetY() - mapCoords.y) * zoom;
		float dx = (objs[i]->GetCurrentAnim()->GetFrameWidth() * scale) * zoom;
		float dy = (objs[i]->GetCurrentAnim()->GetFrameHeight() * scale) * zoom;
		float mx = GetX();
		float my = screen->getHeight() - GetY();
		
		if (mx > x && mx < x+dx && my > y && my < y+dy) tmp.push_back(i); 
	}
	return tmp;
}



void Engine::Save()
{
	if(currentMap == nullptr) return;
}
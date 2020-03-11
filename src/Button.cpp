#include "Button.h"
#include "Screen.h"
#include "utils.h"
#include "Window.h"

using namespace Input;

void ImgButton::Draw()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();
	glBindTexture(GL_TEXTURE_2D,image->texID);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f,1.0f,1.0f);

	float dx = scale * image->width / 3.0f;
	float dy = scale * image->height;

	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	glBegin(GL_QUADS);
		glTexCoord2f((status)*0.3333f,0);	glVertex3f(x,y,0);
		glTexCoord2f((status+1)*0.3333f,0); glVertex3f(x+dx,y,0);
		glTexCoord2f((status+1)*0.3333f,1); glVertex3f(x+dx,y+dy,0);
		glTexCoord2f((status)*0.3333f,1);	glVertex3f(x,y+dy,0);
	glEnd();
}

void ImgButton::Update()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();
	int mx = GetX();
	int my = screen->getHeight() - GetY();

	float dx = scale * image->width / 3.0f;
	float dy = scale * image->height;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	if(GetButtState(0) == KEY_PRESS && status == 2)
		pressed = true;

	if(mx > x && mx < x + dx && my > y && my < y + dy)
	{
		status = 1;
		if(GetButtState(0) == KEY_DOWN)
			status = 2;
	}
	else
	{
		status = 0;
	}
}

void TextButton::Draw()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();

	if(status == 0) glColor3f(1.0f,0,0);
	else if(status == 1) glColor3f(0.5f,0.2f,0.2f);
	else glColor3f(1,1,1);
	
	float textWidth = GetTextLength(text.c_str()) * scale * 20;
	float dx = ((width > textWidth + 6)?width:textWidth+6);
	float dy = 20 * scale + 4;
	float off = (dx - textWidth) / 2;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];
	

	glPrint(x+off,y+4,text.c_str());

	glDisable(GL_TEXTURE_2D);
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(x,y,0);
		glVertex3f(x+dx,y,0);
		glVertex3f(x+dx,y+dy,0);
		glVertex3f(x,y+dy,0);
		glVertex3f(x,y,0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void TextButton::Update()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();
	int mx = GetX();
	int my = screen->getHeight() - GetY(); 

	float textWidth = GetTextLength(text.c_str()) * scale * 20;
	float dx = ((width > textWidth)?width:textWidth) + 6;
	float dy = 16.0f * scale + 4;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	if(GetButtState(0) == KEY_PRESS && status == 2)
		pressed = true;

	if(mx > x && mx < x + dx && my > y && my < y + dy)
	{
		status = 1;
		if(GetButtState(0) == KEY_DOWN)
			status = 2;
	}
	else
	{
		status = 0;
	}
}

void MixedButton::Draw()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();
	glBindTexture(GL_TEXTURE_2D,image->texID);
	glEnable(GL_TEXTURE_2D);

	float textWidth = GetTextLength(text.c_str()) * scale * 20;
	float dx = ((width > textWidth + 6)?width:textWidth+6);
	float dy = 16 * scale + 14;
	float off = (dx - textWidth) / 2;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	glColor3f(1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f((status)*0.3333f,0);	glVertex3f(x,y,0);
		glTexCoord2f((status+1)*0.3333f,0); glVertex3f(x+dx,y,0);
		glTexCoord2f((status+1)*0.3333f,1); glVertex3f(x+dx,y+dy,0);
		glTexCoord2f((status)*0.3333f,1);	glVertex3f(x,y+dy,0);
	glEnd();

	if(status == 0) glColor3f(0.68f,0.61f,0.43f);
	else if(status == 1) glColor3f(1,0.80f,0.05f);
	else glColor3f(1,1,1);	

	glPrint(x+off,y+9 + (scale - 1)*4,text.c_str());
}

void MixedButton::Update()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();
	int mx = GetX();
	int my = screen->getHeight() - GetY(); 

	float textWidth = GetTextLength(text.c_str()) * scale * 20;
	float dx = ((width > textWidth)?width:textWidth) + 6;
	float dy = 16.0f * scale + 14;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	if(GetButtState(0) == KEY_PRESS && status == 2)
		pressed = true;

	if(mx > x && mx < x + dx && my > y && my < y + dy)
	{
		status = 1;
		if(GetButtState(0) == KEY_DOWN)
			status = 2;
	}
	else
	{
		status = 0;
	}
}

void ImgHintButton::Draw()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();
	glBindTexture(GL_TEXTURE_2D,image->texID);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f,1.0f,1.0f);

	float dx = scale * image->width / 3.0f;
	float dy = scale * image->height;

	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	glBegin(GL_QUADS);
		glTexCoord2f((status)*0.3333f,0);	glVertex3f(x,y,0);
		glTexCoord2f((status+1)*0.3333f,0); glVertex3f(x+dx,y,0);
		glTexCoord2f((status+1)*0.3333f,1); glVertex3f(x+dx,y+dy,0);
		glTexCoord2f((status)*0.3333f,1);	glVertex3f(x,y+dy,0);
	glEnd();

	int mx = GetX();
	int my = screen->getHeight() - GetY();
	if(mx > x && mx < x + dx && my > y && my < y + dy)
	{
		glColor3f(0.8,0.8,0.8);
		glPrint(x,y-16,1,hint.c_str());
	}
}

void ImgHintButton::Update()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();
	int mx = GetX();
	int my = screen->getHeight() - GetY();

	float dx = scale * image->width / 3.0f;
	float dy = scale * image->height;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	if(GetButtState(0) == KEY_PRESS && status == 2)
		pressed = true;

	if(mx > x && mx < x + dx && my > y && my < y + dy)
	{
		status = 1;
		if(GetButtState(0) == KEY_DOWN)
			status = 2;
	}
	else
	{
		status = 0;
	}
}
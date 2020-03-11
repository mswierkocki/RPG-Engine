#include "TextControl.h"
#include "utils.h"
#include "OutputManager.h"
#include "Window.h"

using namespace Input;

TextControl::TextControl(Window* parent, float width,bool enable, float dockx, float docky, Pointf OffsetPX, Pointf OffsetPC, float scale)
	:Controlka(parent,dockx,docky,OffsetPX, OffsetPC,scale),width(width),enable(enable)
{
	text = "";
	enter = false;
}

void TextControl::Draw()
{
	if(!visible) return;
	float height = 20 * scale;
	int W = parent->getWidth();
	int H = parent->getHeight();

	float dx = width;
	float dy = height + 2;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + parent->getOffset()[1];

	glBindTexture(GL_TEXTURE_2D,bg->texID);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.1f,0); glVertex3f(x + 10      ,y,0);
		glTexCoord2f(0.9f,0); glVertex3f(x + dx - 10 ,y,0);
		glTexCoord2f(0.9f,1); glVertex3f(x + dx - 10 ,y+dy,0);
		glTexCoord2f(0.1f,1); glVertex3f(x + 10      ,y+dy,0);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);    glVertex3f(x,y,0);
		glTexCoord2f(0.1f,0); glVertex3f(x+10,y,0);
		glTexCoord2f(0.1f,1); glVertex3f(x+10,y+dy,0);
		glTexCoord2f(0,1);    glVertex3f(x,y+dy,0);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.9f,0); glVertex3f(x + dx - 10, y,0);
		glTexCoord2f(1,0);    glVertex3f(x + dx     , y,0);
		glTexCoord2f(1,1);    glVertex3f(x + dx     , y+dy,0);
		glTexCoord2f(0.9f,1); glVertex3f(x + dx - 10, y+dy,0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	//Kursor
	glColor3f(0,0,0);
	if(parent->focus == this)
	{
		float a =  GetTextLength(text.c_str()) * height - 6;
		glBegin(GL_LINES);
			glVertex3f(x + a + 11, y+5, 0);
			glVertex3f(x + a + 18, y+5, 0);

			glVertex3f(x + a + 11, y+6, 0);
			glVertex3f(x + a + 18, y+6, 0);
		glEnd();
	}
	glEnable(GL_TEXTURE_2D);

	glPrint(x+4,y+4,text.c_str());

}

void TextControl::Update()
{
	if(!visible) return;
	if(!enable) return;

	float height = 20 * scale;
	int W = parent->getWidth();
	int H = parent->getHeight();
	int mx = GetX();
	int my = screen->getHeight() - GetY();

	float dx = width;
	float dy = height;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + parent->getOffset()[1];

	if(GetButtState(0) == KEY_DOWN)
	{
		if(mx > x && mx < x + dx && my > y && my < y + dy)	
			parent->focus = this;
		else
			if(parent->focus == this) parent->focus = nullptr;
	}

	int ch = GetChar();
	int key = GetKey();
	if(parent->focus == this)
	{
		if(ch != 0)
		{
			text += (char)ch;
			ClearChar();
		}
		if(key == GLFW_KEY_BACKSPACE && text.length() > 0)
		{
			text = text.substr(0,text.length()-1);
		}
		else if(key == GLFW_KEY_ENTER || key == GLFW_KEY_KP_ENTER)
		{
			enter = true;
		}
		ClearKey();
		InputManager::Consume();
	}
}

////////////////////////////
Texture* TextControl::bg;
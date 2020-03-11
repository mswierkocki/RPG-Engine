#include "SelectControl.h"
#include "Screen.h"
#include "Window.h"
#include "InputManager.h"

using namespace Input;


SelectControl::SelectControl(Window* parent, int max, float width, float dockx, float docky, Pointf OffsetPX, Pointf OffsetPC,  float scale)
	:Controlka(parent,dockx,docky,OffsetPX, OffsetPC,scale),change(false),width(width)
{
	this->max = max;
	pos = 0;
	selected = -1;
	lw = glfwGetMouseWheel();
}

void SelectControl::ForceSelect(int s) //Very dengerous
{
	selected = s;
} 


void SelectControl::Draw()
{
	if(!visible) return;
	float height = 20 * scale;
	int W = parent->getWidth();
	int H = parent->getHeight();
	float dx = width;
	float dy = 20 * max * scale + 4;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	for(unsigned int i = pos; i < list.size() && (i - pos) < max; i++)
	{
		if(selected == i) glColor3f(1,0.80f,0.05f); else glColor3f(0.76f,0.76f,0.76f);
		glPrint(x + 1, y + height*(max - 1 - i + pos) + 3, "%d.   %s",i,list[i].c_str());
	}

	glColor3f(0,0,0);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINE_STRIP);
		glVertex3f(x,y,0);
		glVertex3f(x+dx,y,0);
		glVertex3f(x+dx,y + dy,0);
		glVertex3f(x,y+dy,0);
		glVertex3f(x,y,0);
	glEnd();

	
	glEnable(GL_TEXTURE_2D);

}

void SelectControl::Update()
{
	if(!visible) return;
	float height = 20 * scale;
	int W = parent->getWidth();
	int H = parent->getHeight();
	float dx = width;
	float dy = height * max + 4;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	int mx = GetX() ;
	int my = screen->getHeight() - GetY(); 
	

	if(mx > x && mx < x+dx && my > y && my < y+dy)
	{
		int dw = glfwGetMouseWheel() - lw;
		lw = glfwGetMouseWheel();
		//dw = (dw < 0)?-1:((dw > 0)?1:0);
		//if(dw < 0 && (int)list.size() - pos - 1 < max) dw = 0;
		pos -= dw;
		if(pos > (int)list.size() - max) pos = ((int)list.size() - max);
		if(pos < 0) pos = 0;

		if(GetButtState(0) == State::KEY_DOWN)
		{
			int nr = max - ((my - y) / height);
			
			if(!(nr > (int)list.size() - pos - 1))
			{
				selected = nr + pos;
				change = true;
			}
		}
	}

}

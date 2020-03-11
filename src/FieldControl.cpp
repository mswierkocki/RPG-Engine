#include "FieldControl.h"
#include "Window.h"


FieldControl::FieldControl(Window* parent, float h, float w, float dockx, float docky, Pointf OffsetPX, Pointf OffsetPC)
	:Controlka(parent,dockx,docky,OffsetPX, OffsetPC),w(w),h(h)
{
}

void FieldControl::CountField(float texw, float texh, Pointf& off, Pointf& size)
{
	if(!visible) return;
	size.x = texw;
	size.y = texh;
	if(texh  > h || texw > w)
	{
		float ratio = (texw / w > texh / h) ? texw/w : texh/h;
		size.x = size.x / ratio;
		size.y = size.y / ratio;
	}

	int W = parent->getWidth();
	int H = parent->getHeight();
	off.x = (w - size.x) / 2.0f + (dockX * (W - w)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	off.y = (h - size.y) / 2.0f + (dockY * (H - h)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];
}

void FieldControl::Draw()
{
	//if(!visible) return;
	//int W = parent->getWidth();
	//int H = parent->getHeight();
	//float x = (dockX * (W - w)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	//float y = (dockY * (H - h)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];
	//glDisable(GL_TEXTURE_2D);
	//glColor3f(1,0,0);
	//glBegin(GL_LINE_STRIP);
	//	glVertex3f(x-1  ,y-1,0);
	//	glVertex3f(x+w+2,y-1,0);
	//	glVertex3f(x+w+2,y+h+2,0);
	//	glVertex3f(x-1  ,y+h+2,0);
	//	glVertex3f(x-1  ,y-1,0);
	//glEnd();
	//glEnable(GL_TEXTURE_2D);
}

void FieldControl::Update()
{

}

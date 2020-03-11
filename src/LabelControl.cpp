#include "LabelControl.h"
#include "Window.h"


LabelControl::LabelControl(Window* parent, string text, Color3f color, float dockx, float docky, Pointf OffsetPX, Pointf OffsetPC, float scale)
	:Controlka(parent,dockx,docky,OffsetPX, OffsetPC,scale),text(text),color(color)
{

}

void LabelControl::Draw()
{
	if(!visible) return;
	color.Colorize();
	int W = parent->getWidth();
	int H = parent->getHeight();

	float dx = GetTextLength(text.c_str()) * scale * 20;
	float dy = 20 * scale + 4;
	float x = (dockX * (W - dx)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - dy)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];

	glPrint(x,y,text.c_str());
}

void LabelControl::Update()
{

}

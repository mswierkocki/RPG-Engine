#include "TextureControl.h"
#include "Window.h"


TextureControl::TextureControl(Window* parent, std::string file, float w, float h, float dockx, float docky, Pointf OffsetPX, Pointf OffsetPC)
	:Controlka(parent,dockx,docky,OffsetPX, OffsetPC),w(w),h(h)
{
	texture = new Texture(file);
}

void TextureControl::Draw()
{
	if(!visible) return;
	int W = parent->getWidth();
	int H = parent->getHeight();
	float x = (dockX * (W - w)) / 2.0f + offsetPX[0] + offsetPC[0] * W + parent->getOffset()[0];
	float y = (dockY * (H - h)) / 2.0f + offsetPX[1] + offsetPC[1] * H + parent->getOffset()[1];


	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,texture->texID);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex3f(x,	 y,0);
		glTexCoord2f(1,0); glVertex3f(x + w, y,0);
		glTexCoord2f(1,1); glVertex3f(x + w, y + h,0);
		glTexCoord2f(0,1); glVertex3f(x,	 y + h,0);
	glEnd();
}

void TextureControl::Update()
{
	if(!visible) return;
}

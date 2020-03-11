#include "Animation.h"


Animation::Animation(const std::link<Texture>& tex, int framecount, float framespeed)
{
	texture = tex;
	animSpeed = 1.0;
	animTime = 0;
	currentFrame = 0;
	frameSpeed = framespeed;
	frameCount = framecount;
}

void Animation::Update(double deltaTime)
{
	deltaTime *= animSpeed;

	if(frameCount>1) animTime += deltaTime;

	if((frameCount * frameSpeed)!=0 && frameSpeed!=0)
	{
		animTime = fmod(animTime, frameCount * frameSpeed);
		currentFrame = (int)(animTime/frameSpeed);
	}
}

void Animation::Draw(float x, float y, float dx, float dy)
{
	const float currentx = (float)currentFrame/frameCount;
	const float currentdx = 1.0f/frameCount;

	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,texture->texID);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(currentx,0);           glVertex2f(x,y);
		glTexCoord2f(currentx+currentdx,0); glVertex2f(x+dx,y);
		glTexCoord2f(currentx+currentdx,1); glVertex2f(x+dx,y+dy);
		glTexCoord2f(currentx,1);           glVertex2f(x,y+dy);
	glEnd();
}

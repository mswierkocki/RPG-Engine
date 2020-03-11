#include "Object.h"

Object::Object(float x, float y, float scale):x(x),y(y),scale(scale),animation(0)
{
	scr = new Script("object","StdObj");
	collision = nullptr;
	occlusion = nullptr;
}

Object::~Object()
{
	for(unsigned i=0; i<animations.size(); i++)
		delete animations.at(i);
}

Object::Object(Object& obj)
{
	this->x = obj.x;
	this->y = obj.y;
	this->scale = obj.scale;
	this->animation = obj.animation;
	this->collision = (obj.collision == nullptr)? nullptr : new Poly(obj.collision->points);
	this->occlusion = (obj.occlusion == nullptr)? nullptr : new Poly(obj.occlusion->points);
	this->scriptName = obj.scriptName;
	this->className = obj.className;
	this->scr = new Script("object","StdObj");

	for(unsigned i=0; i<obj.animations.size(); i++)
		this->animations.push_back(std::link<Animation>(new Animation(*obj.animations.at(i)),obj.animations.at(i).Name,obj.animations.at(i).Id,obj.animations.at(i)._Ref));
}

//Object* Object::Copy(float x, float y, float scale, unsigned animation)
//{
//	Object* copy = new Object(x,y,scale);
//
//	for(unsigned i=0; i<animations.size(); i++)
//		copy->GetAnimVecRef().push_back(new Animation(*GetAnimVecRef().at(i)));
//
//	//copy->animation = animation; //may not be necessary
//
//	return copy;
//}

void Object::Update(double deltaTime)
{
	animations[animation]->Update(deltaTime);
	scr->update(deltaTime);
	scr->move(x,y);
}

void Object::Draw()
{

}

void Object::Set(float x, float y, float scale)
{
	this->x = x;
	this->y = y;
	if(scale>0)
		this->scale = scale;
	
	scr->onCreate(x,y,scale);
}

void Object::Move(float x, float y, float scale)
{
	this->x += x;
	this->y += y;
	if(this->scale+scale>0)
		this->scale += scale;
	
	scr->onCreate(x,y,scale);
}

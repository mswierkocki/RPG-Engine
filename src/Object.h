#pragma once

#include "link.hpp"
#include <vector>
#include "Animation.h"
#include "Geometry.h"
#include "Script.h"

class Object
{
protected:
	float x,y;
	float scale;
	std::vector<std::link<Animation>> animations;
	unsigned int animation;
	Poly* collision;
	Poly* occlusion;
	string scriptName;
	string className;
	Script *scr;

public:
	Object(float x = 0, float y = 0, float scale = 1);
	Object(Object& obj);
	Object& operator=(Object& obj);
	~Object();

	Object* Copy(float x = 0, float y = 0, float scale = 1, unsigned int animation = 0);

	void Update(double deltaTime);
	void Draw();


	string GetScriptName() {return scriptName;}
	string GetClassName() {return className;}
	Poly* GetCollision() {return collision;}
	Poly* GetOcclusion() {return occlusion;}
	float GetX() { return x; }
	float GetY() { return y; }
	float GetScale() { return scale; }

	void SetScriptName(string s) {scriptName = s;}
	void SetClassName(string s) {className = s;}
	void SetCollision(Poly* c) {collision = c;}
	void SetOcclusion(Poly* o) {occlusion = o;}
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetScale(float scale) { this->scale = scale; }

	void Set(float x, float y, float scale = 0);
	void Move(float x, float y, float scale = 0);

	void SetAnimation(unsigned int id) { if(id<animations.size()) animation = id; }
	std::vector<std::link<Animation>>& GetAnimVecRef() { return animations; }
	std::link<Animation>& GetCurrentAnim() { return animations[animation]; }
};

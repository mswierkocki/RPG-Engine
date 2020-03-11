#pragma once
#include <stdio.h>
#include <vector>

using namespace std;

struct Pointf
{
public:
	float x,y,z;
	Pointf(float _x = 0, float _y = 0, float _z = 0):x(_x),y(_y),z(_z){}
	Pointf(char* s){
		x = atof(strtok(s," ,"));
		y = atof(strtok(NULL," ,"));
		//z = atof(strtok(NULL," ,"));
	}
	Pointf operator+(Pointf p2) {return Pointf(x+p2.x, y+p2.y);}
	Pointf operator-(Pointf p2) {return Pointf(x-p2.x, y-p2.y);}
	float operator[](int i) {return (i == 0) ? x : ((i == 1) ? y : z);}
	operator float*() {return (float*)this;}
};

class Poly
{
public:
	vector<Pointf> points;
	vector<Pointf> edges;

public:

	Poly(vector<Pointf> points = vector<Pointf>()):points(points) {BuildEdges();}

	void BuildEdges()
	{
		Pointf p1;
		Pointf p2;
		edges.clear();
		for (unsigned int i = 0; i < points.size(); i++) {
			p1 = points[i];
			if (i + 1 >= points.size()) {
				p2 = points[0];
			} else {
				p2 = points[i + 1];
			}
			edges.push_back(p2 - p1);
		}
	}



	Pointf Center() 
	{
		float totalX = 0;
		float totalY = 0;
		for (unsigned int i = 0; i < points.size(); i++) 
		{
			totalX += points[i].x;
			totalY += points[i].y;
		}
		return Pointf(totalX / (float)points.size(), totalY / (float)points.size());
	}

	void Offset(Pointf v)
	{
		Offset(v.x, v.y);
	}

	void Offset(float x, float y) 
	{
		for (unsigned int i = 0; i < points.size(); i++) 
		{
			points[i].x += x;
			points[i].y += y;
		}
	}

};
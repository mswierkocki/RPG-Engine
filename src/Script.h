#pragma once
#include "../Py/Python.h"
#include <string>
#include "error.h"
#define ERR if(PyErr_Occurred()){char a;PyErr_Print();scanf("%c",&a);}

class Script
{
private:

	PyObject *pUpdate;        // funkcje do obslugi Objektu i pochodnych

	PyObject *inst;       // Instancja obiektu w skrypcie
public:
	Script(std::string scriptName = "object", std::string className = "StdObj");
	~Script(void);
	void update(double deltaTime);
	
	void onCreate(float x, float y, float scale);
    void move(float& _x, float& _y);
	//static PyObject object_init(PyObject *self, PyObject
};


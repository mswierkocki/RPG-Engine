#include "Script.h"


Script::Script(std::string scriptName, std::string className)
	{
	PyObject *pModule;
	pModule = PyImport_Import(PyUnicode_FromString(("Content.scripts."+scriptName).c_str()));
    if (pModule) {
		PyObject *pClass = PyObject_GetAttrString(pModule,className.c_str());
		if(pClass != NULL){
			PyObject *arg = PyTuple_New(0);
			inst = PyEval_CallObject(pClass,arg);
			if(inst != NULL)
				pUpdate  = PyObject_GetAttrString(inst,"Update"); /* fetch bound method */
			else
				error("Can't create new instance");
		}
		else
			error("Can't get class ");
	}
	else 
		error("Cant load script '%s'", scriptName.c_str());
	ERR
}


Script::~Script(void)
{
}


void Script::onCreate(float x, float y, float scale){
	PyObject *args;
	args = PyTuple_New(3);
	PyTuple_SetItem(args,0,PyFloat_FromDouble((float)x));
    PyTuple_SetItem(args,1,PyFloat_FromDouble((float)y));
    PyTuple_SetItem(args,2,PyFloat_FromDouble((float)scale));
	PyObject *onCreate;

	if(inst !=NULL){
		onCreate = PyObject_GetAttrString(inst,"onCreate");
		if(onCreate && PyCallable_Check(onCreate))
			PyEval_CallObject(onCreate,args);
		else
			error("can't call onCreate");
	}
	else
		error("cant call OnCreate");
}


void Script::update(double deltaTime){
  if (pUpdate == NULL)
      error("Can't find pUpdate");
  else
	  PyObject_CallObject(pUpdate,Py_BuildValue("(d)", deltaTime));           /* call Update( dt ) */
  ERR
 }


void Script::move(float& _x, float& _y){
	PyObject *result;
	PyObject *args;
	args = PyTuple_New(2);
	PyTuple_SetItem(args,0,PyFloat_FromDouble(_x));
    PyTuple_SetItem(args,1,PyFloat_FromDouble(_y));
	PyObject *fun;

	if(inst !=NULL){
		fun = PyObject_GetAttrString(inst,"Move");
		if(fun && PyCallable_Check(fun))
			result = PyEval_CallObject(fun,args);
		else
			error("can't call Move");
		PyArg_ParseTuple(result,"ff",&_x,&_y);
	}
	else
		error("cant call instance");
}


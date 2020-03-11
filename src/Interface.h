#pragma once
#include "Window.h"
#include "Button.h"

class Interface :public Window
{
private:

	
public:
	Interface();
	void Draw();
	void Update(double deltaTime);

	static void ExitFunc(void* s);

};

/* Dodawanie przyciskow guide 
1.dodanie wskaznika w klasie dziedziczacej po oknie
Button* exitButton;
2. Dodanie w konstruktorze okna
exitButton = new ImgButton(0.93f, 0.90f, 0.07f, "exit2.tga");
3.a) dodanie metody draw do metody draw okna
  b) dodanie metody update do metody update okna
4. Napisanie co sie dzieje po if(exitButton->pressed) do metody update
*/
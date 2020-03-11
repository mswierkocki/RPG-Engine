#pragma once

#include "link.hpp"
#include "Texture.h"

class Animation
{
private:
	//double totalDuration; // calkowity czas animacji, zastapione wynikami modyfikacji konstruktora
	double animTime; // aktualny czas animacji
	double animSpeed; // Mno¿nik prêdkoœci animacji def =1.0
	double frameSpeed; // czas trwania jednej klatki
	int frameCount; // ustalana liczba klatek param konstruktora
	int currentFrame; // ktora klatka aktualnie
	std::link<Texture> texture; // tekstura calej animacji
	
public:
	Animation(const std::link<Texture>& texture, int framecount, float framespeed = 0.25); // nazwa pliku z animacjami, i informacja ile jest w pliku klatek
	// Resetuje cykl animacji
	void Reset() { currentFrame = 0; animTime = 0; }

	void Update(double deltaTime);
	void Draw(float x, float y, float dx, float dy);

	const std::link<Texture> GetTexture() const { return texture; } // Zwraca teksture animacji
	float GetFrameWidth() const { return (float)texture->width/(float)frameCount; } // Zwraca szerokosc ramki
	float GetFrameHeight() const { return (float)texture->height; } // Zwraca wysokosc ramki
	float GetTotalDuration() const { return frameCount*frameSpeed; } // Zwraca calkowity czas trwania animacji

	int GetCurrentFrame() const { return currentFrame; } // Zwraca numer obecnej ramki
	int GetFrameCount() const { return frameCount; } // Zwraca ilosc ramek animacji
	float GetFrameSpeed() const { return frameSpeed; } // Zwraca czas trwania pojedynczej ramki
	float GetAnimSpeed() const { return animSpeed; } // Zwraca predkosc odtwarzania animacji

	void SetCurrentFrame(int frame) { currentFrame = frame; }
	void SetFrameSpeed(double speed) { frameSpeed = speed; } // Ustawia czas trwania jednej klatki
	void SetAnimSpeed(double speed) { animSpeed = speed; }  // Ustawia mno¿nik czasu animacji
};

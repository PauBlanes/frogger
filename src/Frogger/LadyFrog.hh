#pragma once
#include "Sprite.hh"
#include "System.hh"
#include "Tronc.hh"

class LadyFrog {
	friend class Player; //per poder accedir al sprite i al contador sense fer-lo public.	
public:
	LadyFrog();
	void Spawn();
	void Draw();
	bool DetectTronc(Tronc);
private:
	Sprite lFSprite;
	float waitTime;
	bool onScreen;
	float timeOnScreen;
};

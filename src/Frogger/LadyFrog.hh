#pragma once
#include "Sprite.hh"
#include "System.hh"

class LadyFrog {
	friend class Player; //per poder accedir al sprite i al contador sense fer-lo public.	
public:
	LadyFrog();
	void spawn();
	void Draw();
private:
	Sprite lFSprite;
	float waitTime;
	
};

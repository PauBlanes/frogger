#pragma once
#include "Sprite.hh"

class  Granota
{
	friend class Player;
public:
	Granota(int x, int y, int w, int h);
	void arrive();
	void Draw();
private:
	Sprite GranotaSprite;
};

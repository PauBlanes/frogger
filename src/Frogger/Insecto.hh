#pragma once
#include "Sprite.hh"

enum insectPos { Pos1, Pos2, Pos3, Pos4, Pos5};

class Insecto {
	friend class Player;
public:
	Insecto();
	void Move();
	void Draw();
private:
	Sprite insectSprite;
	float waitTime;
	insectPos lastPos;
	insectPos newPos;
};

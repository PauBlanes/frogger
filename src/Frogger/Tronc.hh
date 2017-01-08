#pragma once
#include "Sprite.hh"

enum TroncType {
	small, medium, large
};

class Tronc {
	friend class Player;
public:
	Tronc(int, int, int, int, TroncType, int);
	void Draw();
	void Move();

	
private:
	Sprite tSprite;
	float speed;
	int direction;
	float troncX;
};
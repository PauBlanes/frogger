#pragma once
#include "Sprite.hh"

enum type { coche, camion, rally };

class Vehiculo {
	friend class Player;
public:
	Vehiculo(int, int, int, int, ObjectID, type, int);
	void Draw();
	void Move();
	
	
private:		
	float speed;
	int direction;
	Sprite vSprite;
	float vehicleX;
};
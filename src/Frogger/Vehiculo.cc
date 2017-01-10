
#include "Vehiculo.hh"
#include "Sprite.hh"
#include <iostream>
#include "System.hh"
#include"GameScene.hh"

Vehiculo::Vehiculo(int x, int y, int w, int h, ObjectID mySprite, type tipo, int dir) {
	vSprite = { { x,y , w, h }, mySprite };
	vehicleX = (float)x;
	switch (tipo)
	{
	case coche:
		speed = 0.05;
		break;
	case camion:
		speed = 0.025;
		break;
	case rally:
		speed = 0.15;
		break;	
	}
	direction = dir;
	speed *= GameScene::initMultiplierSpeed;
}

void Vehiculo::Draw() {
	vSprite.Draw();
}

void Vehiculo::Move() {
	
	vehicleX -= (speed * TM.GetDeltaTime() + (float)GameScene::score/900000) * direction;
	vSprite.transform.x = (int)vehicleX;
	if (vSprite.transform.x < 0 && direction == 1) {
		vSprite.transform.x = WIDTH - vSprite.transform.w;
		vehicleX = (float)vSprite.transform.x;
	}
		
	if (vSprite.transform.x > WIDTH && direction == -1) {
		vSprite.transform.x = 0;
		vehicleX = (float)vSprite.transform.x;
	}
		
}


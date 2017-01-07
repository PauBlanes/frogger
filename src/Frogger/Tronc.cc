
#include "Tronc.hh"
#include "Sprite.hh"
#include <iostream>
#include "System.hh"
#include"GameScene.hh"

Tronc::Tronc(int x, int y, int w, int h, TroncType tipus, int dir) {
	troncX = (float)x;
	switch (tipus)
	{
	case small:
		tSprite = { { x,y , w, h }, ObjectID::FUSTA_S };
		break;
	case medium:
		tSprite = { { x,y , w*2, h }, ObjectID::FUSTA_M };
		break;
	case large:
		tSprite = { { x,y , w*4, h }, ObjectID::FUSTA_L };
		break;
	}
	
	speed = 0.1;
	direction = dir;

}

void Tronc::Draw() {
	tSprite.Draw();
}

void Tronc::Move() {
	
	//Moure el tronc
	speed += GameScene::score / 1000; //incremente velocitat en funcio de la score
	troncX -= speed * TM.GetDeltaTime() * direction * GameScene::initMultiplierSpeed;
	tSprite.transform.x = (int)troncX;
	
	if (tSprite.transform.x + tSprite.transform.w < 0 && direction == 1) {
		tSprite.transform.x = WIDTH;
		troncX = (float)tSprite.transform.x;
	}
		
	if (tSprite.transform.x > WIDTH && direction == -1) {
		tSprite.transform.x = 0 - tSprite.transform.w;
		troncX = (float)tSprite.transform.x;
	}
			
}
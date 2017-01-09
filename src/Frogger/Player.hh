#pragma once
#include "Sprite.hh"
#include "vehiculo.hh"
#include "Tronc.hh"
#include "Insecto.hh"
#include "LadyFrog.hh"

class  Player
{
	friend class GameScene;
	
public:
	Player();
	void Move();
	void Draw(void);
	void Die();
	void DetectVehicle(Vehiculo);
	bool DetectTronc(Tronc);
	void DetectRiu(Sprite);
	bool DetectInsecte(Insecto);
	void DetectLadyFrog(LadyFrog);
private:
	Sprite playerSprite;
	int vides;
	bool movimentSegur;
	
	float playerX;
};

 
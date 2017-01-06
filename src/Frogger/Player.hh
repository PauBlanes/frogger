#pragma once
#include "Sprite.hh"
#include "vehiculo.hh"
#include "Tronc.hh"
#include "Insecto.hh"


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
	
private:
	Sprite playerSprite;
	int vides;
	bool movimentSegur;
	bool captureInecte;
	float playerX;
};

 
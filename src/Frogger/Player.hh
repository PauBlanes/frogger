#pragma once
#include "Sprite.hh"
#include "vehiculo.hh"
#include "Tronc.hh"
#include "Insecto.hh"
#include "LadyFrog.hh"

class  Player
{
	friend class GameScene;
	friend class LadyFrog; //per que el ladyFrog pugui accedir al sprite sense fer-lo public, hem posat la comprovacio en el ladyFrog perque sino haviem de passar 
						//com a punter la variable de ladyFrog i llavors ens donava problemes quan intentavem comparar els transforms.
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
	
	float playerX;
};

 
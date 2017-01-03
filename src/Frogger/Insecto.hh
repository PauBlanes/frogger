#pragma once
#include "Sprite.hh"
#include <vector>

class Insecto {
	friend class Player; //per poder accedir al sprite del insecte sense fer-lo public.
	friend class GameScene;//Aix� es perque quan comprovem des del GameScene si est�s colisionant un insecte poguem posar el contador de temps a 0 perqu� salti a una altra posicio.
public:
	Insecto();
	void Move();
	void Draw();
private:
	Sprite insectSprite;
	float waitTime;
	std::vector<int> insectPositions;
	int lastPos;
	int newPos;
};

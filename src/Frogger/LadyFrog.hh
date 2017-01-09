#pragma once
#include "Sprite.hh"
#include "System.hh"
#include "Tronc.hh"


enum ladyState {
	waiting, onPlayer, onScreen
};
class LadyFrog {
	friend class Player; //per que el player pugui accedir al sprite i al contador sense fer-lo public.
	friend class GameScene; //perque el gamescene pugui acecedir al newtroncIndex
public:
	LadyFrog();
	void Update(Tronc, int);
	void Draw();
	
protected:
	Sprite lFSprite;

	float waitTime;	
	float timeOnScreen;

	ladyState state;
	
	int newTroncIndex;
};

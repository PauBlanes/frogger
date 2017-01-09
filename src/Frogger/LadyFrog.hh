#pragma once
#include "Sprite.hh"
#include "System.hh"
#include "Tronc.hh"
#include "Player.hh"

enum ladyState {
	waiting, onPlayer, onScreen
};
class LadyFrog {	
	friend class GameScene; //perque el gamescene pugui acecedir al newtroncIndex
public:
	LadyFrog();
	void Update(Tronc, int, Player);
	void Draw();
	void DetectPlayer(Player);
protected:
	Sprite lFSprite;

	float waitTime;	
	float timeOnScreen;
	int x;
	ladyState state;
	
	int newTroncIndex;
};

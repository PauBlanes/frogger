#include "LadyFrog.hh"


LadyFrog::LadyFrog() {
	lFSprite = { { 0 ,494, 30, 30 },ObjectID::LADYFROG };
	waitTime = 0;
	timeOnScreen = 0;
	state = waiting;
	
}
void LadyFrog::Draw() {
	if (state == onScreen || state == onPlayer)
		lFSprite.Draw();
}

void LadyFrog::Update(Tronc tronc, int troncArraySize, Player pj) {	
	
	switch (state)
	{
	case waiting:
		if (waitTime > 0)
			waitTime -= TM.GetDeltaTime() / 1000;
		else {
			state = onScreen;
			newTroncIndex = rand() % troncArraySize;
		}
		break;
	case onPlayer:
		lFSprite.transform.x = pj.playerSprite.transform.x;
		lFSprite.transform.y = pj.playerSprite.transform.y;
		
		break;
	case onScreen:
		timeOnScreen -= TM.GetDeltaTime() / 1000;

		lFSprite.transform.x = tronc.tSprite.transform.x + tronc.tSprite.transform.w/2;
		lFSprite.transform.y = tronc.tSprite.transform.y;
		
		if (timeOnScreen <= 0) {
			waitTime = 20;
			timeOnScreen = 10;
			state = waiting;
		}
		break;	
	}	
}

void LadyFrog::DetectPlayer(Player pj) {
	
	if (lFSprite.transform.y+lFSprite.transform.h >= pj.playerSprite.transform.y && lFSprite.transform.y <= pj.playerSprite.transform.y + pj.playerSprite.transform.h
		&& lFSprite.transform.x <= pj.playerSprite.transform.x+pj.playerSprite.transform.w && lFSprite.transform.x >= pj.playerSprite.transform.x
		&& state != waiting)
	{
		waitTime = 20; //resetegem els valors per quan torni a estar en espera
		timeOnScreen = 10;
		state = onPlayer;	
		
	}
	if (pj.unaVidaMenys && state == onPlayer) {
		state = waiting;
	}

}

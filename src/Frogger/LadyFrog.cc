#include "LadyFrog.hh"


LadyFrog::LadyFrog() {
	lFSprite = { { WIDTH/2 ,HEIGHT/2, 30, 30 },ObjectID::LADYFROG };
	waitTime = 0;
	timeOnScreen = 0;
	state = waiting;
	
}
void LadyFrog::Draw() {
	if (state == onScreen)
		lFSprite.Draw();
}

void LadyFrog::Update(Tronc tronc, int troncArraySize) {
	
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
		waitTime = 20; //resetegem els valors per quan torni a estar en espera
		timeOnScreen = 10;
		break;
	case onScreen:
		timeOnScreen -= TM.GetDeltaTime() / 1000;

		//lFSprite.transform.x = tronc.tSprite.transform.x;
		//lFSprite.transform.y = tronc.tSprite.transform.y;

		if (timeOnScreen <= 0) {
			waitTime = 20;
			timeOnScreen = 10;
			state = waiting;
		}
		break;	
	}	
}

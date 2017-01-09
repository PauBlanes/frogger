#include "LadyFrog.hh"


LadyFrog::LadyFrog() {
	lFSprite = { { WIDTH/2 ,HEIGHT/2, WIDTH / 15, 30 },ObjectID::INSECT };
	waitTime = 0;
	timeOnScreen = 2;
}
void LadyFrog::Draw() {
	if (onScreen)
		lFSprite.Draw();
}

void LadyFrog::Spawn() {
	if (!onScreen) {
		if (waitTime > 0)
			waitTime -= TM.GetDeltaTime() / 1000;
		else {
			lFSprite.transform.x = 100 + rand() % WIDTH - 100;
			lFSprite.transform.y = 189 + rand() % (HEIGHT / 2 - 189);
			onScreen = true;
		}
	}
	else { 
		timeOnScreen -= TM.GetDeltaTime() / 1000;
		if (timeOnScreen <= 0) {
			waitTime = 5;
			timeOnScreen = 2;
			onScreen = false;
		}
	}
}

bool LadyFrog::DetectTronc(Tronc elTronc) {



	if (lFSprite.transform.y >= elTronc.tSprite.transform.y && lFSprite.transform.y <= elTronc.tSprite.transform.y + elTronc.tSprite.transform.h
		&& lFSprite.transform.x >= elTronc.tSprite.transform.x && lFSprite.transform.x <= elTronc.tSprite.transform.x + elTronc.tSprite.transform.w) {
					
		//playerX -= elTronc.speed * TM.GetDeltaTime() *elTronc.direction; //per alguna rao si en comptes de posar 0.1 poso speed no va. A més em teletransporta a llocs raros
		//playerSprite.transform.x = (int)playerX;
		//2232323

		return true;
	}
	return false;
}
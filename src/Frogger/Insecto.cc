#include "Insecto.hh"
#include "System.hh"
#include <stdlib.h>    
#include <time.h> 

Insecto::Insecto() {
	insectSprite = { { 25 ,128, WIDTH / 15, 30 },ObjectID::INSECT };
	waitTime = 0;
	lastPos = Pos1;
	srand(time(NULL));
}

void Insecto::Draw() {
	insectSprite.Draw();
}
void Insecto::Move() {	
	if (waitTime > 0)
		waitTime -= TM.GetDeltaTime() / 1000;
	else {
		newPos = (insectPos)(rand() % 6);
		if (newPos != lastPos) {
			switch (newPos)
			{
			case Pos1:
				insectSprite.transform.x = 25;
				break;
			case Pos2:
				insectSprite.transform.x = 190;
				break;
			case Pos3:
				insectSprite.transform.x = 355;
				break;
			case Pos4:
				insectSprite.transform.x = 520;
				break;
			case Pos5:
				insectSprite.transform.x = 680;
				break;
			}
			waitTime = 5;
			lastPos = newPos;
		}

	}
}
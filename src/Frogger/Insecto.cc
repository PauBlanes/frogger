#include "Insecto.hh"
#include "System.hh"
#include <stdlib.h>    
#include <time.h> 

Insecto::Insecto() {
	insectSprite = { { 25 ,128, WIDTH / 15, 30 },ObjectID::INSECT };
	waitTime = 0;

	
	lastPos = -1; //aixi la primera vegada que instanciem l'insecte ens deixa fer-ho perque newPos != lastPos;

	srand(time(NULL));
}

void Insecto::Draw() {
	insectSprite.Draw();
	
}
void Insecto::Move() {	
	if (insectPositions.size() > 1) {
		if (waitTime > 0)
			waitTime -= TM.GetDeltaTime() / 1000;
		else {
			newPos = rand() % insectPositions.size();
			if (newPos != lastPos) { //aixo es per no repetir posicions
				insectSprite.transform.x = insectPositions[newPos];
				waitTime = 5;
				lastPos = newPos;
			}
		}
	} else insectSprite.transform.x = insectPositions[0];
	
}
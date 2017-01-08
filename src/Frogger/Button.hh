#pragma once

#include "Sprite.hh"
#include "ID.hh"

class Button {	
public:
	Button();
	void SetCoords(int, int, int, int, ObjectID);
	void Draw(void);
	bool ICliked();
private:
	Sprite buttonSprite;

};

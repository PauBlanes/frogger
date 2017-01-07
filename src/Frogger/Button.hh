#pragma once

#include "Sprite.hh"
#include "ID.hh"

class Button {
	friend class StartScene;//per poder utilitzar el transform i centrar b� els botons
public:
	Button();
	void SetCoords(int, int, int, int, ObjectID);
	void Draw(void);
	bool ICliked();
private:
	Sprite buttonSprite;

};

#pragma once

#include "System.hh"
#include "Button.hh"
#include <iostream>



Button::Button() {
	buttonSprite = { { WIDTH / 6 * 3,420 , WIDTH / 15, 30 }, ObjectID::PLAYBUTTON};
}

void Button::SetCoords(int x, int y, int w, int h, ObjectID myID) {
	buttonSprite = { { x,y , w, h }, myID };
}
void Button::Draw(void) {

	buttonSprite.Draw();
}

bool Button::ICliked() {

	MouseCoords mouseCoords = IM.GetMouseCoords();
	if (buttonSprite.transform.x < mouseCoords.x &&
		buttonSprite.transform.y < mouseCoords.y &&
		buttonSprite.transform.x + buttonSprite.transform.w > mouseCoords.x &&
		buttonSprite.transform.y + buttonSprite.transform.h > mouseCoords.y) {
		std::cout << "Click" << std::endl;
		return true;
	}
	else
		return false;
 
	
}

#include "DifficultyScene.hh"

/*
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
using namespace rapidxml;
using namespace std;
*/

using namespace Logger;

DifficultyScene::DifficultyScene(void) {

	background = { { 0,0, W.GetWidth(), W.GetHeight() }, ObjectID::FONDOMENU };

	easyButton.SetCoords(WIDTH/4 + 15, (HEIGHT >> 1) / 2 + 50, 350, 50, ObjectID::OP1);
	mediumButton.SetCoords(WIDTH / 4 + 15, (HEIGHT >> 1) / 2 + 150, 350, 50, ObjectID::OP2);
	hardButton.SetCoords(WIDTH / 4 + 15, (HEIGHT >> 1) / 2 + 250, 350, 50, ObjectID::OP3);
	toMenu.SetCoords(20, 20, 100, 100, ObjectID::TOMENUBUTTON);
}

DifficultyScene::~DifficultyScene(void) {
}

void DifficultyScene::OnEntry(void) {
}

void DifficultyScene::OnExit(void) {
}

void DifficultyScene::Update(void) {
	
	if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		if (easyButton.ICliked()) {			
			GameScene::difficulty = "easy";
			SM.SetCurScene<GameScene>();
		}
		else if (mediumButton.ICliked()) {			
			GameScene::difficulty = "medium";
			SM.SetCurScene<GameScene>();
		}
		else if (hardButton.ICliked()) {			
			GameScene::difficulty = "hard";
			SM.SetCurScene<GameScene>();
		}
		else if (toMenu.ICliked()) {			
			SM.SetCurScene<StartScene>();
		}
	}
}

void DifficultyScene::Draw(void) {
	background.Draw();
	easyButton.Draw();
	mediumButton.Draw();
	hardButton.Draw();
	toMenu.Draw();	
}

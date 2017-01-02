/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "StartScene.hh"
#include "DifficultyScene.hh"
#include "SceneManager.hh"



using namespace Logger;



StartScene::StartScene(void) {
	
	m_background = { { 0,0, W.GetWidth(), W.GetHeight() }, ObjectID::FONDOMENU };
	Titol = { { 175 ,(HEIGHT >> 1) / 2, 350, 50 }, ObjectID::TITOL };
	playButton.SetCoords(WIDTH/2-50, 320, WIDTH / 7, 75, ObjectID::PLAYBUTTON);
	exitButton.SetCoords(20, 20, WIDTH / 15, 50, ObjectID::EXITBUTTON);
}

StartScene::~StartScene(void) {
}

void StartScene::OnEntry(void) {
}

void StartScene::OnExit(void) {
}

void StartScene::Update(void) {
	//Comprovar mouse
	if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		if (playButton.ICliked())
			SM.SetCurScene<DifficultyScene>();
		else if (exitButton.ICliked())
			SDL_Quit();
	}	

}

void StartScene::Draw(void) {
	m_background.Draw(); //PINTEM EL FONS
	Titol.Draw();
	playButton.Draw(); //Pintem el botó
	exitButton.Draw();
	
}
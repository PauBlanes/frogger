/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/


#include "StartScene.hh"



using namespace Logger;



StartScene::StartScene(void) {
	
	m_background = { { 0,0, W.GetWidth(), W.GetHeight() }, ObjectID::FONDOMENU };
	Titol = { {75 ,(HEIGHT >> 1) / 2, 600, 100 }, ObjectID::TITOL };
	playButton.SetCoords(WIDTH/2 - 125, HEIGHT/2-50, 250, 150, ObjectID::PLAYBUTTON);
	exitButton.SetCoords(20, 20, WIDTH / 15, 50, ObjectID::EXITBUTTON);
	top10Button.SetCoords(WIDTH/2 - 75, HEIGHT/2 + 200, 150, 150, ObjectID::TOP10BUTTON);
	
}

StartScene::~StartScene(void) {
}

void StartScene::OnEntry(void) {
	SDL_StopTextInput(); //Per defecte el textInput esta activat i aquesta es la primera escena aixi que el desactivem. Si no ho fem totes les tecles que haviem pulsat en escenes anteriors es guardaven.
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
		else if (top10Button.ICliked()) {
			RankingsScene::sP = justDrawing;
			SM.SetCurScene<RankingsScene>();			
		}
			
	}	

}

void StartScene::Draw(void) {
	m_background.Draw(); //PINTEM EL FONS
	Titol.Draw();
	playButton.Draw(); //Pintem el botó
	exitButton.Draw();
	top10Button.Draw();	
}
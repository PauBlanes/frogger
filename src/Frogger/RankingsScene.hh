#pragma once
#include "Scene.hh"
#include "GameScene.hh"
#include "GUI.hh"
#include "System.hh"
#include <vector>
#include "Button.hh"
#include "StartScene.hh"

const int userNameLength = 10;

struct userRank
{
	char userName [userNameLength]; //despres de molts errors hem vist que el millor es tenir una mida fixa del nom si no volem estar iterant per llegir.
	int score;	
};

enum scenePhase { askingUsername, updatingScore, justDrawing }; //el tercer es per no utilitzar un bool i estar fent un update de la score i per tant accedint al fitxer tota la estona

class RankingsScene : public Scene {
	
public:
	explicit RankingsScene();
	~RankingsScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void UpdateRanking(void);	
	static scenePhase sP; //aixo ens serveix per organitzar que fer al update i al draw. També ho utilitzem pq des del Menu ho canviem quan entrem a aquesta escena per no demanar el username
private:
	userRank newUser;
	
	std::string userInput; //aqui guardem el input del usuari perque era més fàcil fer-ho amb strings i despres passar-ho a array de chars.	
	
	std::vector <userRank> highScores;

	Button toMenu;
};
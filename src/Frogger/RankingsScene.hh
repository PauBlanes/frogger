#pragma once
#include "Scene.hh"
#include "GameScene.hh"
#include "GUI.hh"
#include "System.hh"
#include <vector>


const int userNameLength = 10;

struct userRank
{
	char userName [userNameLength];
	int score;	
};

enum scenePhase { askingUsername, updatingScore, justDrawing }; //el tercer es per no utilitzar un bool i estar fent un update de la score i per tant accedint al fitxer tota la estona

class RankingsScene : public Scene {
	friend class InputManager;
public:
	explicit RankingsScene();
	~RankingsScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void UpdateRanking(void);
	
private:
	userRank newUser;
	
	std::string userInput;
	
	scenePhase sP; //aixo ens serveix per organitzar que fer al update i al draw
	
	std::vector <userRank> highScores;
};
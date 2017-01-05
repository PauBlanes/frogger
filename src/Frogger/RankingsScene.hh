#pragma once
#include "Scene.hh"
#include "GameScene.hh"
#include "GUI.hh"
#include "System.hh"
#include <vector>


struct userRank
{
	char userName [5];
	int score;	
};

class RankingsScene : public Scene {
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
	
	char getUserName[5];
	std::vector <userRank> scoresToSend;
	std::vector <userRank> highScores;
};
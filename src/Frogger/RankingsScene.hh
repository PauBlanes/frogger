#pragma once
#include "Scene.hh"
#include "GameScene.hh"


struct userRank
{
	char* userName;
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
private:
	userRank user1;
	userRank user2;
	userRank user3;

	std::vector <userRank> highScores;
};
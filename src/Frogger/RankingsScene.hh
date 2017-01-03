#pragma once
#include "Scene.hh"
#include "GameScene.hh"

class RankingsScene : public Scene {
public:
	explicit RankingsScene();
	~RankingsScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	
};
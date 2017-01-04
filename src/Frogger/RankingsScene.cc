#include "RankingsScene.hh"
#include "IOManager.hh"

RankingsScene::RankingsScene(void) {
	
}

RankingsScene::~RankingsScene(void) {
}

void RankingsScene::OnEntry(void) {

	user1.userName = "Manuel";
	user1.score = GameScene::score;
	IOManager::WriteBin("../../res/cfg/rankings.bin", user1);
	IOManager::ReadBin("../../res/cfg/rankings.bin");
	
}

void RankingsScene::OnExit(void) {
}

void RankingsScene::Update(void) {
	
}

void RankingsScene::Draw(void) {
	
}
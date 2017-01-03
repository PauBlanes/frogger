#include "RankingsScene.hh"
#include "IOManager.hh"

RankingsScene::RankingsScene(void) {
	
}

RankingsScene::~RankingsScene(void) {
}

void RankingsScene::OnEntry(void) {
	IOManager::WriteBin("../../res/cfg/rankings.bin", "Manuel", GameScene::score);
	cout << IOManager::ReadBin("../../res/cfg/rankings.bin") << endl;
}

void RankingsScene::OnExit(void) {
}

void RankingsScene::Update(void) {
	
}

void RankingsScene::Draw(void) {
	
}
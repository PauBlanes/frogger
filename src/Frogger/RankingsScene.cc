#include "RankingsScene.hh"
#include "IOManager.hh"

RankingsScene::RankingsScene(void) {
	
}

RankingsScene::~RankingsScene(void) {
}

void RankingsScene::OnEntry(void) {

	user1 = { "Manuel", 5 };
	user2 = { "Paco", 18 };
	user3 = { "Pau", 10 };
	
	//IOManager::WriteBin("../../res/cfg/rankings.bin", user1);
//	IOManager::WriteBin("../../res/cfg/rankings.bin", user2);
	IOManager::WriteBin("../../res/cfg/rankings.bin", user3);
	
//	IOManager::ReadBin("../../res/cfg/rankings.bin");
	
}

void RankingsScene::OnExit(void) {
}

void RankingsScene::Update(void) {
	
}

void RankingsScene::Draw(void) {
	
}
#include "RankingsScene.hh"
#include "IOManager.hh"

RankingsScene::RankingsScene(void) {
	
}

RankingsScene::~RankingsScene(void) {
}

void RankingsScene::OnEntry(void) {

	user1 = { "AAA", 5 };
	user2 = { "Pa", 1888 };
	user3 = { "paub", 107 };
	scoresToSend.push_back(user1);
	scoresToSend.push_back(user2);
	scoresToSend.push_back(user3);
	IOManager::WriteBin("../../res/cfg/rankings.bin", scoresToSend, 1);
	//IOManager::WriteBin("../../res/cfg/rankings.bin", user2, 2);
	//IOManager::WriteBin("../../res/cfg/rankings.bin", user1,3);	
	
	highScores = IOManager::ReadBin("../../res/cfg/rankings.bin");
	
	for (auto& i : highScores) {
		cout << i.userName << ":" << i.score << endl;
	}
		
}

void RankingsScene::OnExit(void) {
}

void RankingsScene::Update(void) {
	
}

void RankingsScene::Draw(void) {
	GUI::DrawTextBlended<FontID::ARIAL>("Write your username : ",
	{ WIDTH/2, HEIGHT/2-200, 1, 1 },
	{ 255, 0, 0 }); // Render score that will be different when updated
	
	
}
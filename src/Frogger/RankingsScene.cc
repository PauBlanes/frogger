#include "RankingsScene.hh"
#include "IOManager.hh"

RankingsScene::RankingsScene(void) {
	
}

RankingsScene::~RankingsScene(void) {
}

void RankingsScene::OnEntry(void) {
	
	UpdateRanking();	
		
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

void RankingsScene::UpdateRanking(void) {
	
	highScores = IOManager::ReadBin("../../res/cfg/rankings.bin"); //hem de llegir perquè quan tornem a executar el vector estarà buit.
	
	newUser = { "Juan", GameScene::score };

	//si esta buit omplim amb jugadors model
	if (highScores.empty()) { 
		cout << "buit" << endl;
		for (int i = 0; i < 10;i++) {
			userRank temp = { "ABC", i };
			highScores.push_back(temp);
		}
		IOManager::WriteBin("../../res/cfg/rankings.bin", highScores, 1);
	}

	//escriurem la nostra puntuacio+puntaucions inferiors, així no hem d'escriure les 10 cada vegada	
	int position = 1; //per saber a partir on haurem d'enviar
		
	for (auto &i : highScores) {
		if (newUser.score >= i.score) {
			//cout << "Hola" << endl;
			vector<userRank>::iterator first = highScores.begin() + (position-1);
			vector<userRank>::iterator last = highScores.begin() + 9; //no ens deixa fer highScors.end()-1, però això serà el mateix
			vector<userRank> toWrite(first, last); //copiem totes les puntuacions inferiors per escriure a partir d'aqui al fitxer de rankings.
			toWrite.insert(toWrite.begin(), newUser);
			IOManager::WriteBin("../../res/cfg/rankings.bin", toWrite, position);				
		}
		else
			position++;
	}
		
	
	
	cout << "TOP 10 JUGADORS" << endl;
	highScores = IOManager::ReadBin("../../res/cfg/rankings.bin");
	for (auto& i : highScores) {
		cout << i.userName << ":" << i.score << endl;
	}
}
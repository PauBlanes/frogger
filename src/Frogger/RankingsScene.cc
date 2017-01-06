#include "RankingsScene.hh"
#include "IOManager.hh"

RankingsScene::RankingsScene(void) {
	
}

RankingsScene::~RankingsScene(void) {
}

void RankingsScene::OnEntry(void) {
	
	SDL_StartTextInput();
	sP = askingUsername;
	
}

void RankingsScene::OnExit(void) {
	
}

void RankingsScene::Update(void) {
	
	if (sP == askingUsername) {
		
		if (IM.IsKeyDown<SDLK_RETURN>()) {
			SDL_StopTextInput();
			sP = updatingScore;
		}

		userInput = IM.GetInputText();
				
		if (userInput.size() >= userNameLength) { //Si ens passem del tamany de nom d'usuari permès no deixem escriure més.
			if (SDL_TEXTINPUT)
				SDL_StopTextInput();

		}
		if (IM.IsKeyDown<SDLK_BACKSPACE>()) { //Si hem apagat el text input però borrem i tornem a estar dins del tamany permès de nom d'usuari hem de tornar a activar el text input.
			SDL_StartTextInput();
		}
		
	}
	else if (sP == updatingScore) {
		UpdateRanking();
		sP = justDrawing;
	}
		
		
	
}

void RankingsScene::Draw(void) {
	
	if (sP == askingUsername) { //Pintem el text inicial i el nom que estas escribint
		GUI::DrawTextBlended<FontID::ARIAL>("USERNAME : " + userInput,
		{ WIDTH / 2, HEIGHT / 2 - 200, 1, 1 },
		{ 0, 0, 0 }); 
	}	
	else if (sP == justDrawing) { //Pintem les puntuacions
		
		GUI::DrawTextBlended<FontID::ARIAL>("TOP 10 PLAYERS (EASY)",
		{ WIDTH / 2, HEIGHT / 2 - 300, 1, 1 },
		{ 0, 0, 0 });
		
		for (int i = 0; i < userNameLength;i++) {
			
			GUI::DrawTextBlended<FontID::ARIAL>(std::to_string(i + 1) + ". " + highScores[i].userName + ":" + std::to_string(highScores[i].score),
			{ WIDTH / 2, HEIGHT / 2 - 200 + 60 * i, 1, 1 },
			{ 0, 0, 0 }); 
		}
	}
	
}

void RankingsScene::UpdateRanking(void) {
	
	highScores = IOManager::ReadBin("../../res/cfg/rankings.bin"); //hem de llegir perquè quan tornem a executar el vector estarà buit.	
	
	strcpy(newUser.userName, userInput.c_str());
	newUser.score = GameScene::score;
		
	//si esta buit omplim amb jugadors model
	if (highScores.empty()) { 
		cout << "buit" << endl;
		for (int i = 10; i > 0;i--) {
			userRank temp = { "ABC", i };
			highScores.push_back(temp);
		}
		IOManager::WriteBin("../../res/cfg/rankings.bin", highScores, 1);
	}

	//escriurem la nostra puntuacio+puntaucions inferiors, així no hem d'escriure les 10 cada vegada	
	int position = 0; //per saber a partir on haurem d'enviar
		
	for (auto &i : highScores) {
		if (newUser.score >= i.score) {
			
			vector<userRank>::iterator first = highScores.begin(); //+ (position-1)
			vector<userRank>::iterator last = highScores.begin() + 9; //no ens deixa fer highScors.end()-1, però això serà el mateix
			vector<userRank> toWrite(first, last); //copiem totes les puntuacions inferiors per escriure a partir d'aqui al fitxer de rankings.
			toWrite.insert(toWrite.begin() + position, newUser);
			
			IOManager::WriteBin("../../res/cfg/rankings.bin", toWrite, position);
		}
		else
			position++;
	}
	for (auto& i : highScores) {
		cout << i.userName << endl;
	}
	highScores = IOManager::ReadBin("../../res/cfg/rankings.bin"); //actualitzem per pintar la ultima puntuacio que hem afegit
	for (auto& i : highScores) {
		cout << i.userName << endl;
	}
	
}
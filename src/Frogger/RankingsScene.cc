#include "RankingsScene.hh"
#include "IOManager.hh"

scenePhase RankingsScene::sP;

RankingsScene::RankingsScene(void) {
	sP = askingUsername; //ho posem aqui perque aixi si hem de canviar-ho des d'una altra escena per no ahver d'escriure el username no tindrem problemes.
	toMenu.SetCoords(20, 20,100, 100, ObjectID::TOMENUBUTTON);
	r_background = { { -150,0, W.GetWidth()+300, W.GetHeight() }, ObjectID::FONDORANKINGS };
	
}

RankingsScene::~RankingsScene(void) {
}

void RankingsScene::OnEntry(void) {
	
	highScores = IOManager::ReadBin("../../res/cfg/",GameScene::difficulty); //hem de llegir perquè quan tornem a executar el vector estarà buit.
	SDL_StartTextInput();
	
	
}

void RankingsScene::OnExit(void) {
	sP = askingUsername;//per si hem entrat des del menu primer
	
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

	//Si clickem el botó de retorn al menu
	if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) 
		if (toMenu.ICliked())
			SM.SetCurScene<StartScene>();	
	
}

void RankingsScene::Draw(void) {
	
	r_background.Draw();

	if (sP == askingUsername) { //Pintem el text inicial i el nom que estas escribint
		GUI::DrawTextBlended<FontID::ARIAL>("USERNAME : " + userInput,
		{ WIDTH / 2, HEIGHT / 2 - 200, 1, 1 },
		{ 0, 0, 0 }); 
	}	
	else if (sP == justDrawing) { //Pintem les puntuacions
		
		GUI::DrawTextBlended<FontID::ARIAL>("TOP 10 PLAYERS ( " + GameScene::difficulty + " )",
		{ WIDTH / 2, HEIGHT / 2 - 300, 1, 1 },
		{ 0, 0, 0 });
		
		for (int i = 0; i < userNameLength;i++) {
			
			GUI::DrawTextBlended<FontID::ARIAL>(std::to_string(i + 1) + ". " + highScores[i].userName + ":" + std::to_string(highScores[i].score),
			{ WIDTH / 2, HEIGHT / 2 - 200 + 60 * i, 1, 1 },
			{ 0, 0, 0 }); 
		}
	}

	toMenu.Draw();	
}

void RankingsScene::UpdateRanking(void) {		
	
	//Omplim el nou usuari
	strcpy(newUser.userName, userInput.c_str());
	newUser.score = GameScene::score;
	userInput = "A";
	cout << userInput << endl;
	//si esta buit omplim amb jugadors model
	if (highScores.empty()) { 
		cout << "buit" << endl;
		for (int i = 10; i > 0;i--) {
			userRank temp = { "ABC", i };
			highScores.push_back(temp);
		}
		IOManager::WriteBin("../../res/cfg/",GameScene::difficulty, highScores, 1);
	}

	//escriurem la nostra puntuacio+puntaucions inferiors, així no hem d'escriure les 10 cada vegada	
	int position = 0; //per saber a partir on haurem d'enviar
		
	for (auto &i : highScores) {
		if (newUser.score >= i.score) {
			
			vector<userRank>::iterator first = highScores.begin(); //+ (position-1)
			vector<userRank>::iterator last = highScores.begin() + 9; //no ens deixa fer highScors.end()-1, però això serà el mateix
			vector<userRank> toWrite(first, last); //copiem totes les puntuacions inferiors per escriure a partir d'aqui al fitxer de rankings.
			toWrite.insert(toWrite.begin() + position, newUser);
			
			IOManager::WriteBin("../../res/cfg/", GameScene::difficulty,toWrite, position);
		}
		else
			position++;
	}
	
	highScores = IOManager::ReadBin("../../res/cfg/", GameScene::difficulty); //actualitzem per pintar la ultima puntuacio que hem afegit
	
	
}

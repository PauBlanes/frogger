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
	userInput = "";
}

void RankingsScene::Update(void) {
	
	switch (sP)
	{
	case askingUsername:
		if (IM.IsKeyDown<SDLK_RETURN>()) { //quan l'usuari apreti enter el nom queda acceptat
			SDL_StopTextInput();
			sP = updatingScore;
		}

		userInput = IM.GetInputText();

		if (userInput.size() == userNameLength) { //Si ens passem del tamany de nom d'usuari permès no deixem escriure més.
			if (SDL_TEXTINPUT)
				SDL_StopTextInput();
		}
		if (IM.IsKeyDown<SDLK_BACKSPACE>()) { //Si hem apagat el text input però borrem i tornem a estar dins del tamany permès de nom d'usuari hem de tornar a activar el text input.
			SDL_StartTextInput();
		}
		break;
	case updatingScore:
		UpdateRanking();
		break;
	case drawingRanking:
		if (highScores.empty())
			sP = buit;
		break;	
	}
	
	//Si clickem el botó de retorn al menu
	if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) 
		if (toMenu.ICliked())
			SM.SetCurScene<StartScene>();	
	
}

void RankingsScene::Draw(void) {
	
	r_background.Draw();
	switch (sP)
	{
	case askingUsername:
		GUI::DrawTextBlended<FontID::ARIAL>("USERNAME : " + userInput,
		{ WIDTH / 2, HEIGHT / 2 - 200, 1, 1 },
		{ 0, 0, 0 });
		break;
	case updatingScore:
		break;
	case etsUnFracassat:
		GUI::DrawTextBlended<FontID::ARIAL>(userInput + "(" + std::to_string(GameScene::score) + " punts) es un bon nom per",
		{ WIDTH / 2, HEIGHT / 2, 1, 1 },
		{ 0, 0, 0 });
		GUI::DrawTextBlended<FontID::ARIAL>("un jugador professional de parchís...",
		{ WIDTH / 2, HEIGHT / 2 + 100, 1, 1 },
		{ 0, 0, 0 });
		break;
	case drawingRanking:
		GUI::DrawTextBlended<FontID::ARIAL>("TOP 10 PLAYERS ( " + GameScene::difficulty + " )",
		{ WIDTH / 2, HEIGHT / 2 - 300, 1, 1 },
		{ 0, 0, 0 });

		for (int i = 0; i < userNameLength;i++) {

			GUI::DrawTextBlended<FontID::ARIAL>(std::to_string(i + 1) + ". " + highScores[i].userName + ":" + std::to_string(highScores[i].score),
			{ WIDTH / 2, HEIGHT / 2 - 200 + 60 * i, 1, 1 },
			{ 0, 0, 0 });
		}
		break;
	case buit:
		GUI::DrawTextBlended<FontID::ARIAL>("There are no highscores...yet",
		{ WIDTH / 2, HEIGHT / 2, 1, 1 },
		{ 0, 0, 0 });
		GUI::DrawTextBlended<FontID::ARIAL>("GO PLAY",
		{ WIDTH / 2, HEIGHT / 2 + 100, 1, 1 },
		{ 0, 0, 0 });
		break;
		break;	
	}
		
	
	

	toMenu.Draw();	
}

void RankingsScene::UpdateRanking(void) {		
	
	//Omplim el nou usuari
	strcpy(newUser.userName, userInput.c_str());
	newUser.score = GameScene::score;
	
	//si esta buit omplim amb jugadors model
	if (highScores.empty()) { 
		
		for (int i = 10; i > 0;i--) {
			userRank temp = { "A PLAYER", i };
			highScores.push_back(temp);
		}
		IOManager::WriteBin("../../res/cfg/",GameScene::difficulty, highScores, 1);
	}
	//escriurem la nostra puntuacio+puntaucions inferiors, així no hem d'escriure les 10 cada vegada	
	int position = 0; //per saber a partir on haurem d'enviar
	sP = etsUnFracassat; //si en cap moment tens una puntuació millor que alguna del top10 no entrà al if i no es posarà el mode de pintar la puntuació.
	for (auto &i : highScores) {
		cout << newUser.score << " vs " << i.score << endl;
		if (newUser.score >= i.score) {			
			vector<userRank>::iterator first = highScores.begin(); //+ (position-1)
			vector<userRank>::iterator last = highScores.begin() + 9; //no ens deixa fer highScors.end()-1, però això serà el mateix
			vector<userRank> toWrite(first, last); //copiem totes les puntuacions inferiors per escriure a partir d'aqui al fitxer de rankings.
			toWrite.insert(toWrite.begin() + position, newUser);			
			IOManager::WriteBin("../../res/cfg/", GameScene::difficulty,toWrite, position);
			sP = drawingRanking;
		}
		else
			position++;
	}
	
	highScores = IOManager::ReadBin("../../res/cfg/", GameScene::difficulty); //actualitzem per pintar la ultima puntuacio que hem afegit
	
	
}

/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include "SceneManager.hh"
#include "IOManager.hh"
#include <stdlib.h>    
#include <time.h>
#include "LadyFrog.hh"

using namespace std;
using namespace Logger;

std::string GameScene::difficulty;
int GameScene::score;
int GameScene::initMultiplierSpeed;
float GameScene::timeDivider;

GameScene::GameScene() {	
	
	//Escenari
	FONDO = { { 0, HEIGHT/2, WIDTH, HEIGHT /2 }, ObjectID::FONDO };
	AIGUA = { { 0, 0, WIDTH, HEIGHT / 2 }, ObjectID::AIGUA };
	CamiInicial = { { 0,HEIGHT-120-pj.playerSprite.transform.h/2 ,WIDTH, 60 },ObjectID::CAMI };
	CamiMig = { { 0,HEIGHT - (HEIGHT/16)*6-120- pj.playerSprite.transform.h / 2 ,WIDTH, 60 },ObjectID::CAMI };
	TERRA = { { 0,75 ,WIDTH, 100 },ObjectID::TERRA };
	

	//Settejar els contadors per instanciar els vehicles
	counterLinia1 = 0.5 + rand()%1;
	counterLinia2 = 0.75 + rand() % 1;;
	counterLinia3 = 0.75 + rand() % 1;;
	counterLinia4 = 0.5 + rand() % 1;
	counterLinia5 = 0.2 + rand()%1;

	srand(time(NULL));	

	//Botons del Menu de Pausa
	PMResume.SetCoords(WIDTH / 2 - 175, HEIGHT/2-150, 350, 100, ObjectID::PMRESUME);
	PMRestart.SetCoords(WIDTH / 2 - 175, HEIGHT / 2, 350, 100, ObjectID::PMRESTART);
	PMToMenu.SetCoords(WIDTH / 2 - 175, HEIGHT / 2 +150, 350, 100, ObjectID::PMTOMENU);
}

GameScene::~GameScene(void){
}

void GameScene::OnEntry(void) {
	
	

	//Llegim les dades al xml
	vector <string> infoXML = IOManager::ReadXML("../../res/cfg/LvLSettings.xml", difficulty);
	initMultiplierSpeed = atoi(infoXML[0].c_str());
	pj.vides = atoi(infoXML[1].c_str());
	timeDivider = atof(infoXML[2].c_str());

	cout << "Inicial speed multiplied by: "<< initMultiplierSpeed << endl;
	cout << "Hp: "<< pj.vides << endl;
	cout << "Time divider: " <<timeDivider << endl;	

	score = 0;

	//El temporitzador
	timeCounter = 60/GameScene::timeDivider;
	timeBar = { { 200, HEIGHT - 60 ,240, 30 },ObjectID::TIMEBAR };

	//Resetegem el jugador
	pj.playerSprite.transform.x = WIDTH / 2;
	pj.playerSprite.transform.y = HEIGHT - 120;
	pj.playerX = (float)(WIDTH >> 1);

	vehicleArray.clear();//aixo ho fem pq sino al tornar a entrar des d'una altra escena teniem el doble de cotxes perque es tornen a instanciar aquests.
	//GameObjects inicials. Els vehicles els posem aqui pq sino aquestst que son els incials no tenen el multiplicador de velocitat del xml pq al constructor encara no l'hem llegit.
	//linia 1: rallys TARONGES
	InsertVehicle(WIDTH - 100, HEIGHT - (HEIGHT / 16) - 120, WIDTH / 15, 30, ObjectID::RALLY_NARANJA, rally, 1); // 120 es el marge que deixcem a baix per el contador de temps
																												 //linia2: cotxes BLANCS	
	InsertVehicle(WIDTH / 2, HEIGHT - (HEIGHT / 16) * 2 - 120, WIDTH / 15, 30, ObjectID::COTXE_BLANCO, coche, -1);
	//linia3 : cotxes ROSES
	InsertVehicle(WIDTH - 100, HEIGHT - (HEIGHT / 16) * 3 - 120, WIDTH / 15, 30, ObjectID::COTXE_ROSA, coche, 1);
	InsertVehicle(WIDTH - 300, HEIGHT - (HEIGHT / 16) * 3 - 120, WIDTH / 15, 30, ObjectID::COTXE_ROSA, coche, 1);
	//linia4: rallys VERMELL
	InsertVehicle(500, HEIGHT - (HEIGHT / 16) * 4 - 120, WIDTH / 15, 30, ObjectID::RALLY_ROJO, rally, -1);
	//linia5: camiones
	InsertVehicle(WIDTH / 2, HEIGHT - (HEIGHT / 16) * 5 - 120, WIDTH / 15, 30, ObjectID::CAMIO, camion, 1);
	
	troncArray.clear();
	//TRONCS
	//linia 1
	InsertTronc(WIDTH - 200, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16), 100, 40, large, 1);
	InsertTronc(0, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16), 100, 40, large, 1);
	//linia2
	InsertTronc(0, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 2, 150, 40, small, -1);
	InsertTronc(300, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 2, 150, 40, small, -1);
	InsertTronc(600, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 2, 150, 40, small, -1);
	//linia3
	InsertTronc(150, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 3, 100, 40, (TroncType)(rand() % 3), 1);
	//linia4
	InsertTronc(300, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 4, 100, 40, (TroncType)(rand() % 3), -1);
	//linia5
	InsertTronc(0, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 5, 100, 40, medium, 1);
	InsertTronc(350, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 5, 100, 40, medium, 1);
	InsertTronc(650, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 5, 100, 40, medium, 1);


	//Aquests son les xs dels forats del final
	limitRana = { { 20,85 },{ 180,255 },{ 340,415 },{ 500,580 },{ 665,740 } };
	GranotaArray.clear();//per si sortim de la escena i tornem a entrar des d'una altra
	RanaNum = 0;
	casellaFinalBona = false;//aixo ho utilitzem per saber si estema  uan casella final nova o no

	//Insecte
	insect.insectPositions = { 25,190,355,520,680 };

	//Calculem quants vehicles de cada tipus hi haur� (nosaltres ho fem per linia, �s a dir el doble en el cas dels cotxes i rallys.)
	numCotxes = 3 + nivel % 3;
	numRallys = 1 + nivel % 3;
	numCamions = 2 + nivel % 3;
}

void GameScene::OnExit(void) {
	if (isPaused)
		isPaused = !isPaused;
}

void GameScene::Update(void) {
	
	if (!isPaused) { //aixo ho posem aqui perque volem que nomes funcioni en aquesta escena i sino al apretar esc no podriem clickar botons en altres escenes. Tamb� el problema seria que heuriem de tenir la comprovacio del input del esc per pausar aqui i la de despausar en el GameEngine, i ens sembla millor fer-ho tot aqui ja que nom�s ha de funcionar per aquesta escena.

		//Actualitzem el contador de temps
		if (timeCounter >0)
			timeCounter -= TM.GetDeltaTime()/1000;
		else {
			if (pj.vides > 1) {
				pj.vides--;
				pj.playerSprite.transform.x = (WIDTH >> 1);
				pj.playerSprite.transform.y = HEIGHT - 120;
			}
				
			else
				pj.Die();
			timeCounter = 60*GameScene::timeDivider;
		}
		timeBar.transform.w = timeCounter*4*GameScene::timeDivider;//aqui tornem a multiplicar epr el divisor perqu� volem que les barrres sempre tinguin el mateix tamany, per� baixin m�s r�pid
		
		//Mirem si el personatge es mou
		pj.Move();
		
		//insertem vehicles fins que hi ha els que toca
		WaitAndInsert();

		//movem el insect cada 5 segons
		insect.Move();
		
		//posar la ladyFrog a waiting
		if (lF.state == onPlayer)
			lF.state = waiting;

		//Moure vehivles i detectar colisions
		for (int i = 0;i < vehicleArray.size();i++) {
			vehicleArray[i].Move();
			pj.DetectVehicle(vehicleArray[i]);
		}
		aCapTronc = true;
		for (int i = 0;i < troncArray.size();i++) {

			troncArray[i].Move();
			if (pj.DetectTronc(troncArray[i]))
				aCapTronc = false;

		}
		if (aCapTronc && pj.playerSprite.transform.y >= 189)//si el jugador no est� colisionant amb cap tronc llavors mirem si colisiona amb el riu
			pj.DetectRiu(AIGUA);	

		
		//aqui comprovem si esta en una casella que no pertany a larray.
		if (pj.playerSprite.transform.y < 188) { //si esta a la al�ada de la pantalla que toca
			for (int i = 0; i < limitRana.size();i++) { //no podem fer el auto& it pq volem borrar coses
				
				if (pj.playerSprite.transform.x >= limitRana[i].first && pj.playerSprite.transform.x <= limitRana[i].second && pj.playerSprite.transform.y < 188) { //comprovem per a cada un dels forats buits	i amb la y pq quan tornis al mig no pinti a la tercera casella			
					
					if (!pj.DetectInsecte(insect)) {
						score += (50 + timeCounter*10);
						timeCounter = 60 / GameScene::timeDivider;
					}
					else { //si hi ha insecte sumem 200
						score += 200;
						insect.waitTime = 0; //el fem saltar a una altra posicio inmediatament
					} 

					if (lF.state == onPlayer) { //si el player porta la lasy frog
						score += 200;
					}					
					InsertGranota(limitRana[i].first + 10, 120, WIDTH / 15, 50); //insertem la granota i tornem el pj al principi
					limitRana.erase(limitRana.begin() + i); //borrem les Xs d'aquest forat perqu� ja no sigui segur i moris si hi tornes a entrar
					insect.insectPositions.erase(insect.insectPositions.begin() + i);//com que aquest array est� ordenat igual que el de minX i maxX dels forats podem borrar el mateix index pq l'insecte noe s pinti a caselles on ja hi ha granota.
										
					pj.playerSprite.transform.x = (WIDTH >> 1);
					pj.playerSprite.transform.y = HEIGHT - 120;

					RanaNum++;
					casellaFinalBona = true;

					if (RanaNum == 5) {
						score += 1000;
						RanaNum = 0;
						pj.Die();
					}
					
				}
				pj.movimentSegur = false; //no volem que tamb� tinguis els 10 punts per aquest moviment perque ja est�s aconseguint els 50 per arrivar al final
			}

			if (!casellaFinalBona) { //hem de posar aix� fora del for perqu� primer comprovi el if amb tots els forats.
				if (pj.vides > 0) {
					pj.playerSprite.transform.x = (WIDTH >> 1);
					pj.playerSprite.transform.y = HEIGHT - 120;
					pj.vides -= 1;
					pj.unaVidaMenys = true;
				}
			}
			else
				casellaFinalBona = false;
		}

		//Un cop hem detectat colisons sabrem si hem mogut a casella segura o no
		if (pj.movimentSegur && pj.playerSprite.transform.y > 188) {
			score += 10;
			pj.movimentSegur = false;
		}

		//Tot lady Frog
		lF.DetectPlayer(pj);
		lF.Update(troncArray[lF.newTroncIndex], troncArray.size(), pj);
		pj.unaVidaMenys = false;

		//Mort del personatge
		if (pj.vides <= 0) {
			pj.Die();			
		}
		
	}

	else {
		if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
			if (PMRestart.ICliked()) 
				SM.SetCurScene<DifficultyScene>();							
			if (PMResume.ICliked())
				isPaused = false;
			if (PMToMenu.ICliked())
				SM.SetCurScene<StartScene>();
		}
	}
	
	if (IM.IsKeyDown<SDLK_ESCAPE>())
		isPaused = !isPaused;
	
}

void GameScene::Draw(void) {
	
	FONDO.Draw();
	AIGUA.Draw();
	TERRA.Draw();
	CamiInicial.Draw();
	CamiMig.Draw();
	timeBar.Draw();

	//Bucle per vehicles
	for (int i = 0;i < vehicleArray.size();i++) {
		vehicleArray[i].Draw();
	}
	//Pintar Troncs
	for (int i = 0;i < troncArray.size();i++) {
		troncArray[i].Draw();
		
	}

	//Pintar L'insecte
	insect.Draw();

	//pintar Granotes
	for (int i = 0; i < GranotaArray.size(); i++) {
		GranotaArray[i].Draw();
	}

	 //El personatge
	 pj.Draw();

	 //Pintar la puntuacio
	 GUI::DrawTextBlended<FontID::ARIAL>("Score: " + std::to_string(score),
	 { W.GetWidth() >> 1, int(40), 1, 1 },
	 {255, 0, 0 }); // Render score that will be different when updated

	 //pintar les vides
	 GUI::DrawTextBlended<FontID::ARIAL>("Health: " + std::to_string(pj.vides),
	 { WIDTH-100, int(HEIGHT-45), 1, 1 },
	 { 255, 0, 0 }); // Render score that will be different when updated

	 //Pintar el temps
	 GUI::DrawTextBlended<FontID::ARIAL>("TIME: " + std::to_string((int)timeCounter) + "s",
	 { 95, HEIGHT - 45, 1, 1 },
	 { 255, 0, 0 }); // Render score that will be different when updated
	
	 lF.Draw();

	 if (isPaused) {
		 PMResume.Draw();
		 PMRestart.Draw();
		 PMToMenu.Draw();
	 }
}

void GameScene::InsertVehicle(int x, int y, int w, int h, ObjectID mySprite, type tipo, int dir) {
	
	
		Vehiculo newV(x, y, w, h, mySprite, tipo, dir);
		vehicleArray.push_back(newV);
		
}
void GameScene::InsertTronc(int x, int y, int w, int h, TroncType tipus, int dir) {
	Tronc newT(x, y, w, h, tipus, dir);
	troncArray.push_back(newT);

}
void GameScene::WaitAndInsert() {	
	
	//linia 1
	if (counterLinia1 > 0 && counterLinia1 != 48) {
		counterLinia1 -= TM.GetDeltaTime() / 1000;
	}
	else if (counterLinia1 <= 0 && counterLinia1 != 48) {		
		if (numRallys - 1 > 0) { //el -1 es perque ja hi ha un rally incial
			InsertVehicle(WIDTH, HEIGHT - (HEIGHT / 16) - 120, WIDTH / 15, 30, ObjectID::RALLY_NARANJA, rally, 1);
			counterLinia1 = 1;
			numRallys--;
		}
		else
			counterLinia1 = 48;
	}

	//linia 2
	if (counterLinia2 > 0 && counterLinia2 != 48) {
		counterLinia2 -= TM.GetDeltaTime() / 1000;
	}
	else if (counterLinia2 <= 0 && counterLinia2 != 48) {
		if (numCotxes - 1 > 0) { //el -1 es perque ja hi ha un cotxe incial
			InsertVehicle(0, HEIGHT - (HEIGHT / 16) * 2 - 120, WIDTH / 15, 30, ObjectID::COTXE_BLANCO, coche, -1);
			counterLinia2 = 1;
			numCotxes--;
		}
		else
			counterLinia2 = 48;
	}

	//linia 3
	if (counterLinia3 > 0 && counterLinia3 != 48) {
		counterLinia3 -= TM.GetDeltaTime() / 1000;
	}
	else if (counterLinia3 <= 0 && counterLinia3 != 48) {
		if (numCotxes - 2 > 0) { //el -1 es perque ja hi ha 2 cotxes inicials
			InsertVehicle(WIDTH, HEIGHT - (HEIGHT / 16) * 3 - 120, WIDTH / 15, 30, ObjectID::COTXE_ROSA, coche, 1);
			counterLinia3 = 1;
			numCotxes--;
		}
		else
			counterLinia3 = 48;
	}

	//linia 4
	if (counterLinia4 > 0 && counterLinia4 != 48) {
		counterLinia4 -= TM.GetDeltaTime() / 1000;
	}
	else if (counterLinia4 <= 0 && counterLinia4 != 48) {
		if (numRallys - 1 > 0) { //el -1 es perque ja hi ha un rally incial
			InsertVehicle(0, HEIGHT - (HEIGHT / 16) * 4 - 120, WIDTH / 15, 30, ObjectID::RALLY_ROJO, rally, -1);
			counterLinia4 = 1;
			numRallys--;
		}
		else
			counterLinia4 = 48;
	}

	//linia 5
	if (counterLinia5 > 0 && counterLinia5 != 48) {
		counterLinia5 -= TM.GetDeltaTime() / 1000;
	}
	else if (counterLinia5 <= 0 && counterLinia5 != 48) {
		if (numCamions - 1 > 0) { //el -1 es perque ja hi ha un camio incial
			InsertVehicle(WIDTH, HEIGHT - (HEIGHT / 16) * 5 - 120, WIDTH / 15, 30, ObjectID::CAMIO, camion, 1);
			counterLinia5 = 1;
			numCamions--;
		}
		else
			counterLinia5 = 48;
	}
	
}
void GameScene::InsertGranota(int x, int y, int w, int h) {
		Granota newG(x, y, w, h);
		GranotaArray.push_back(newG);
}
	
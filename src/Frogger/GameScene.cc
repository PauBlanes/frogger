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

	//TRONCS
	//linia 1
	InsertTronc(WIDTH - 200, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16), 100, 40,large, 1);
	InsertTronc(0, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16), 100, 40, large, 1);
	//linia2
	InsertTronc(0, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16)*2, 150, 40, small, -1);
	InsertTronc (300, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 2, 150, 40, small, -1);
	InsertTronc(600, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16) * 2, 150, 40, small, -1);
	//linia3
	InsertTronc(150, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16)*3, 100, 40, (TroncType)(rand() % 3), 1);
	//linia4
	InsertTronc(300, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16)*4, 100, 40, (TroncType)(rand() % 3), -1);
	//linia5
	InsertTronc(WIDTH - 200, CamiMig.transform.y + pj.playerSprite.transform.h / 2 - (HEIGHT / 16)*5, 100, 40, (TroncType)(rand() % 3), 1);

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

	//Aquests son les xs dels forats del final
	limitRana = { { 20,85 },{ 185,250 },{ 345,410 },{ 505,575 },{ 670,735 } };
	//RanaNum = 0;
	casellaFinalBona = false;//aixo ens servira per saber si estema  uan casella final nova o no
	

	//Calculem quants vehicles de cada tipus hi haurà (nosaltres ho fem per linia, és a dir el doble en el cas dels cotxes i rallys.)
	numCotxes = 3 + nivel % 3;
	numRallys = 1 + nivel % 3;
	numCamions = 2 + nivel % 3;
}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {
	
	pj.Move();

	//insertem vehicles fins que hi ha els que toca
	WaitAndInsert();

	//movem el insect cada 5 segons
	insect.Move();
	//comprovar si el pj ha agafat el insecte
	pj.DetectInsecte(insect);

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
	if(aCapTronc && pj.playerSprite.transform.y >= 189 )//si el jugador no està colisionant amb cap tronc llavors mirem si colisiona amb el riu
		pj.DetectRiu(AIGUA);
		
	
	//Un cop he detectat colisons sabre si me mogut a casella segura o no
	if (pj.movimentSegur && pj.playerSprite.transform.y > 188) {
		score += 10;
		pj.movimentSegur = false;
	}

	
	//cout << insect.insectPositions.size() << endl;
	//aqui comprovem si esta en una casella que no pertany a larray.
	if (pj.playerSprite.transform.y < 188) { //si esta a la alçada de la pantalla que toca
		pj.movimentSegur = false; //no volem que també tinguis els 10 punts per aquest moviment perque ja estàs aconseguint els 50 per arrivar al final
		for (int i = 0; i < limitRana.size();i++) { //no podem fer el auto& it pq volem borrar coses
				
			std::cout << limitRana[i].first << "," << limitRana[i].second << std::endl;
			std::cout << pj.playerSprite.transform.x << std::endl;
			if (pj.playerSprite.transform.x >= limitRana[i].first && pj.playerSprite.transform.x + pj.playerSprite.transform.w <= limitRana[i].second) { //comprovem per a cada un dels forats buits				
				
				InsertGranota(limitRana[i].first, 120, WIDTH / 15, 50); //insertem la granota i tornem el pj al principi
				pj.playerSprite.transform.x = (WIDTH >> 1);
				pj.playerSprite.transform.y = HEIGHT - 120;
				
				RanaNum++;
				casellaFinalBona = true;
				limitRana.erase(limitRana.begin() + i); //borrem les Xs d'aquest forat perquè ja no sigui segur i moris si hi tornes a entrar
				if (pj.DetectInsecte(insect)) {
					cout << "Hola" << endl;
					insect.waitTime = 0; //el fem saltar a una altra posicio inmediatament
					insect.insectPositions.erase(insect.insectPositions.begin() + i);//com que aquest array està ordenat igual que el de minX i maxX dels forats podem borrar el mateix index pq l'insecte noe s pinti a caselles on ja hi ha granota.
					score += 200;
				}					
				else
					score += 50;

				if (RanaNum == 5) {
					score += 1000;
					RanaNum = 0;
				}
			}
		};
		
		if (casellaFinalBona == false) { //hem de posar això fora del for perquè primer comprovi el if amb tots els forats.
			if (pj.vides > 0) {
				pj.playerSprite.transform.x = (WIDTH >> 1);
				pj.playerSprite.transform.y = HEIGHT - 120;
				pj.vides -= 1;
			}
			else
				pj.Die();
			
		}
		else
			casellaFinalBona = false;
	}
	
	
}

void GameScene::Draw(void) {
	
	FONDO.Draw();
	AIGUA.Draw();
	TERRA.Draw();
	CamiInicial.Draw();
	CamiMig.Draw();

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
	 { 100, int(HEIGHT-45), 1, 1 },
	 { 255, 0, 0 }); // Render score that will be different when updated
	
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
	
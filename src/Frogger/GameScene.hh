/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once

#include "Scene.hh"
#include "Sprite.hh"
#include "Player.hh"
#include "vehiculo.hh"
#include "Tronc.hh"
#include <vector>
#include "Insecto.hh"
#include "Granota.hh"
#include "Button.hh"

// GameScene class with the main gameplay mode
class GameScene : public Scene {
	
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void InsertVehicle(int, int, int, int, ObjectID, type, int);
	void InsertTronc(int, int, int, int, TroncType, int);
	void InsertGranota(int, int, int, int);
	void WaitAndInsert();
	static std::string difficulty;
	static int score;
	static int initMultiplierSpeed;
	static float timeDivider;
private:
	
	//Sprite m_background;
	Sprite FONDO;
	Sprite AIGUA;
	Sprite TERRA;
		
	Sprite CamiInicial, CamiMig;

	Insecto insect;
	
	float counterLinia1; //aixo es per tenir diferents cooldowns depenent de les linies de la carretera i així no tots els vehicles estaran igual de junts.
	float counterLinia2;
	float counterLinia3;
	float counterLinia4;
	float counterLinia5;

	int numCotxes;
	int numRallys;
	int numCamions;
	
	std::vector<Vehiculo> vehicleArray;
	std::vector<Tronc> troncArray;

	std::vector<Granota> GranotaArray;
	std::vector<std::pair<int, int>> limitRana; //aquest array conte les minX i maxX dels forats.
	int RanaNum; //amb aquest numero sabrem si has salvat totes les granotes	
	
	bool casellaFinalBona; 

	bool aCapTronc; //aquest bool nomes es false si no estàs tocant cap tronc de la escena. Si és false comprovarem si estàs tocant el riu.	

	Player pj;

	int nivel;	

	//Contador de temps
	float timeCounter;
	Sprite timeBar;

	//Menu de Pausa
	bool isPaused;//utilitzarem això per pausar el joc
	Button PMResume;
	Button PMRestart;
	Button PMToMenu;
	
};
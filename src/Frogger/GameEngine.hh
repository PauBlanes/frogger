/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "System.hh"

#pragma region GAME_SCENES
#include "GameScene.hh"
#include "StartScene.hh"
#include "DifficultyScene.hh"
#include "RankingsScene.hh"

#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadFont<FontID::CANDY>("fnt/candy.ttf", 50);
		R.LoadFont<FontID::FACTORY>("fnt/candsb.ttf", 80);
		
		//Buttons
		R.LoadTexture<ObjectID::PLAYBUTTON>("gfx/playButton.png");
		R.LoadTexture<ObjectID::EXITBUTTON>("gfx/exitButton.png");		
		R.LoadTexture<ObjectID::OP1>("gfx/FACIL.png");
		R.LoadTexture<ObjectID::OP2>("gfx/NORMAL.png");
		R.LoadTexture<ObjectID::OP3>("gfx/DIFICIL.png");
		R.LoadTexture<ObjectID::TOP10BUTTON>("gfx/top10Icon.png");
		R.LoadTexture<ObjectID::TOMENUBUTTON>("gfx/backToMenu.jpg");

		//StartScene
		R.LoadTexture<ObjectID::TITOL>("gfx/TITOL.png");
		R.LoadTexture<ObjectID::FONDOMENU>("gfx/fondoMenu.png");
		
		//GameScene
		R.LoadTexture<ObjectID::FONDO>("gfx/fondo.png");
		R.LoadTexture<ObjectID::RALLY_ROJO>("gfx/COTXE_ROJO.png");
		R.LoadTexture<ObjectID::RALLY_NARANJA>("gfx/COTXE_NARANJA.png");
		R.LoadTexture<ObjectID::COTXE_BLANCO>("gfx/COTXE_BLANCO.png");
		R.LoadTexture<ObjectID::COTXE_ROSA>("gfx/COTXE_ROSA.png");
		R.LoadTexture<ObjectID::CAMIO>("gfx/CAMIO.png");
		R.LoadTexture<ObjectID::TORTUGA>("gfx/TORTUGA.png");
		R.LoadTexture<ObjectID::COCODRIL>("gfx/COCODRIL.png");
		R.LoadTexture<ObjectID::FUSTA_L>("gfx/FUSTA01.png");
		R.LoadTexture<ObjectID::FUSTA_M>("gfx/FUSTA02.png");
		R.LoadTexture<ObjectID::FUSTA_S>("gfx/FUSTA03.png");
		R.LoadTexture<ObjectID::CAMI>("gfx/RIU.png");
		R.LoadTexture<ObjectID::AIGUA>("gfx/aigua.png");
		R.LoadTexture<ObjectID::TERRA>("gfx/TERRA.png");
		R.LoadTexture<ObjectID::PJBASIC>("gfx/G_S_C.png");
		R.LoadTexture<ObjectID::INSECT>("gfx/mosquito.png");
		R.LoadTexture<ObjectID::GRANOTA>("gfx/GRANOTA.png");
	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<GameScene>();
		SM.AddScene<StartScene>();
		SM.AddScene<DifficultyScene>();
		SM.AddScene<RankingsScene>();
		SM.SetCurScene<StartScene>();		
//		
	}
	/** 
	 * Runs the game specifying the window's name and dimensions
	 * @tparam screenWidth Determines the window's width
	 * @tparam screenHeight Determines the window's height
	 * @param name Determines the window's title
	 */
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes
		bool m_isRunning{ true }; // Decides if the game loop is running
		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)
		while (!IM.HasQuit() && m_isRunning) { // Checks while game's still playable
			TM.FPSBegin(); // Calculates the time difference for deltaTime and FPS limiting purposes
			#pragma region GAME_UPDATE
				switch (m_curScene->GetState()) { // Check for the state of the screen
					case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
					case SceneState::EXIT:		m_isRunning = false; break; // Triggers an end of the game looping
					case SceneState::SLEEP: default:;
				}
			#pragma endregion
			#pragma region GAME_DRAW
				TM.FPSEnd([&]() { // Limits the FPS rendering with a lambda function as the parameter that draws the whole game
					if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
						R.Clear();			// Clear the screen buffer
						m_curScene->Draw(); // Call the draw method of the scene
						R.Render();			// Update the screen buffer with all sprites that were pushed
					}});
			#pragma endregion
		}
	}
}
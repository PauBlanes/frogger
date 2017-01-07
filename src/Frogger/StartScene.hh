#pragma once
#include "Scene.hh"
#include "Sprite.hh"
#include "Button.hh"
#include "DifficultyScene.hh"
#include "SceneManager.hh"
#include "RankingsScene.hh"
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"

class StartScene : public Scene {
public:
	explicit StartScene();
	~StartScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background;
	Sprite Titol;
	Button playButton;
	Button exitButton;
	Button top10Button;
};

#pragma once

#include "Scene.hh"
#include "Sprite.hh"
#include "Button.hh"
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include "StartScene.hh"

// GameScene class with the main gameplay mode
class DifficultyScene : public Scene {
	
public:
	explicit DifficultyScene();
	~DifficultyScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	
private:
	Sprite background;
	Button easyButton;
	Button mediumButton;
	Button hardButton;
	Button toMenu;
};
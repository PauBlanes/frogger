#pragma once

#include "Scene.hh"
#include "Sprite.hh"
#include "Button.hh"

// GameScene class with the main gameplay mode
class DifficultyScene : public Scene {
	
public:
	explicit DifficultyScene();
	~DifficultyScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void writeXML(int);
private:
	Sprite background;
	Button easyButton;
	Button mediumButton;
	Button hardButton;
	
};
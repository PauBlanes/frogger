#pragma once
#include "Scene.hh"
#include "Sprite.hh"
#include "Button.hh"

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

};

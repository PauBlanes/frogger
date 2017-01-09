#pragma once
#include "System.hh"
#include "Player.hh"
#include "GameScene.hh"
#include "GUI.hh"
#include "RankingsScene.hh"

Player::Player() {
	playerSprite = { { (WIDTH >> 1),HEIGHT-120, WIDTH / 15, 30 },ObjectID::PJBASIC};
	movimentSegur = false;
	
	playerX = (float)(WIDTH >> 1);
}

void Player::Move() {
	
	if (IM.IsKeyDown<'w'>() && playerSprite.transform.y - HEIGHT / 16 >100) {
		playerSprite.transform.y -= HEIGHT / 16;
		playerX = (float)playerSprite.transform.x;
		movimentSegur = true;
	}
	if (IM.IsKeyDown<'s'>() && playerSprite.transform.y + HEIGHT / 16 < HEIGHT-100) {		
		playerSprite.transform.y += HEIGHT / 16;
		playerX = (float)playerSprite.transform.x;
	}
	if (IM.IsKeyDown<'a'>() && playerSprite.transform.x - WIDTH/10 > 0) {		
		playerSprite.transform.x -= WIDTH/10;
		playerX = (float)playerSprite.transform.x;
	}
	if (IM.IsKeyDown<'d'>() && playerSprite.transform.x + playerSprite.transform.w + WIDTH/10 < WIDTH) {		
		playerSprite.transform.x += WIDTH/10;
		playerX = (float)playerSprite.transform.x;
	}
		
}

void Player :: Draw(void) {
	playerSprite.Draw();
}
void Player::Die() {
	//quan s'acavin les vides escriure game over
	GUI::DrawTextBlended<FontID::ARIAL>("YOU DIE!",
	{ int(W.GetWidth()*0.35), int(W.GetHeight()*0.5f), 2, 2 },
	{ 115, 0, 180 });

	SM.SetCurScene<RankingsScene>();
}

void Player::DetectVehicle(Vehiculo collider) {
	
	if (playerSprite.transform.y >= collider.vSprite.transform.y && playerSprite.transform.y <= collider.vSprite.transform.y + collider.vSprite.transform.h
		&& playerSprite.transform.x+playerSprite.transform.w >= collider.vSprite.transform.x && playerSprite.transform.x <= collider.vSprite.transform.x + collider.vSprite.transform.w) {

		if (vides > 1) { //Si encara li queden vides el tornem al principi
			vides -= 1;
			playerSprite.transform.x = (WIDTH >> 1);
			playerSprite.transform.y = HEIGHT - 120;
			movimentSegur = false;
		}
		else {
			Die();
		}
		
	}	
}

bool Player::DetectTronc(Tronc elTronc) {

	

	if (playerSprite.transform.y >= elTronc.tSprite.transform.y && playerSprite.transform.y <= elTronc.tSprite.transform.y + elTronc.tSprite.transform.h
		&& playerSprite.transform.x >= elTronc.tSprite.transform.x && playerSprite.transform.x <= elTronc.tSprite.transform.x + elTronc.tSprite.transform.w) {
		if (IM.IsKeyDown<'d'>()) {
			playerX += HEIGHT / 16;
			playerSprite.transform.x = (int)playerX;
		}
		if (IM.IsKeyDown<'a'>()) {
			playerX -= HEIGHT / 16;
			playerSprite.transform.x = (int)playerX;
		}
		else {
			if (playerX > 0 && playerX + playerSprite.transform.w < WIDTH) {
				playerX -= elTronc.speed * TM.GetDeltaTime() *elTronc.direction;
				playerSprite.transform.x = (int)playerX;
			}			
		}		
		return true;
	}
	return false;
}

void Player::DetectRiu( Sprite Riu) {	
	
		if (playerSprite.transform.y >= Riu.transform.y && playerSprite.transform.y <= Riu.transform.y + Riu.transform.h
			&& playerSprite.transform.x + playerSprite.transform.w >= Riu.transform.x && playerSprite.transform.x <= Riu.transform.x + Riu.transform.w
			) {
			if (vides > 1) { //Si encara li queden vides el tornem al principi
				vides -= 1;
				playerSprite.transform.x = (WIDTH >> 1);
				playerSprite.transform.y = HEIGHT - 120;
				movimentSegur = false;
			}
			else {
				Die();
			}
		}		
}
bool Player::DetectInsecte(Insecto insect) {
	
	if (playerSprite.transform.y <= insect.insectSprite.transform.y && playerSprite.transform.y <= insect.insectSprite.transform.y + insect.insectSprite.transform.h
		&& playerSprite.transform.x + playerSprite.transform.w >= insect.insectSprite.transform.x && playerSprite.transform.x <= insect.insectSprite.transform.x + insect.insectSprite.transform.w)
	{		
		
		insect.waitTime = 0; //el fem saltar a una altra posicio inmediatament
		playerSprite.transform.x = (WIDTH >> 1);
		playerSprite.transform.y = HEIGHT - 120;
		movimentSegur = false;
		return true;
	}
	return false;
}

void Player::DetectLadyFrog(LadyFrog lF) {

	std::cout << playerSprite.transform.y << " P F " << lF.lFSprite.transform.y << std::endl;
	if (playerSprite.transform.y <= lF.lFSprite.transform.y && playerSprite.transform.y <= lF.lFSprite.transform.y + lF.lFSprite.transform.h /*
		&& playerSprite.transform.x + playerSprite.transform.w >= lF.lFSprite.transform.x && playerSprite.transform.x <= lF.lFSprite.transform.x + lF.lFSprite.transform.w*/)
	{
		
		lF.state = onPlayer;
		lF.lFSprite.transform.x = playerSprite.transform.x;
		lF.lFSprite.transform.y = playerSprite.transform.y;
		
	}
	
}


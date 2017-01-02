#pragma once
#include "System.hh"
#include "Granota.hh"

Granota::Granota(int x, int y, int w, int h) {
	GranotaSprite = { { x,y , w, h }, ObjectID::GRANOTA };
}

void Granota::arrive() {

}

void Granota::Draw() {
	GranotaSprite.Draw();
}


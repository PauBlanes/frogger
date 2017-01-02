#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "DifficultyScene.hh"
#include "GameScene.hh"

/*
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
using namespace rapidxml;
using namespace std;
*/

using namespace Logger;

DifficultyScene::DifficultyScene(void) {

	background = { { 0,0, W.GetWidth(), W.GetHeight() }, ObjectID::FONDOMENU };

	easyButton.SetCoords(WIDTH/4, (HEIGHT >> 1) / 2 + 50, 350, 50, ObjectID::OP1);
	mediumButton.SetCoords(WIDTH / 4, (HEIGHT >> 1) / 2 + 125, 350, 50, ObjectID::OP2);
	hardButton.SetCoords(WIDTH / 4, (HEIGHT >> 1) / 2 + 200, 350, 50, ObjectID::OP3);
		
}

DifficultyScene::~DifficultyScene(void) {
}

void DifficultyScene::OnEntry(void) {
}

void DifficultyScene::OnExit(void) {
}

void DifficultyScene::Update(void) {
	
	if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		if (easyButton.ICliked()) {
			//writeXML(1);
			GameScene::difficulty = "easy";
			SM.SetCurScene<GameScene>();
		}
		else if (mediumButton.ICliked()) {
			//writeXML(2);
			GameScene::difficulty = "medium";
			SM.SetCurScene<GameScene>();
		}
		else if (hardButton.ICliked()) {
			//writeXML(3);
			GameScene::difficulty = "hard";
			SM.SetCurScene<GameScene>();
		}			
	}
}

void DifficultyScene::Draw(void) {
	background.Draw();
	easyButton.Draw();
	mediumButton.Draw();
	hardButton.Draw();
	
	
}
/* 
//Intent d'escriure en un fitxer xml, però no acaba de funcionar quan ho ajunto amb la lectura, de moment només llegim.
void DifficultyScene::writeXML(int difficulty) {
	cout << "Escribint" << endl;
	xml_document<> doc;
	
	//Read the xml file into a vector
	ifstream theFile("Proves.xml");
	
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<rapidxml::parse_no_data_nodes>(&buffer[0]);
	xml_node<> * root_node;
	// Find our root node
	root_node = doc.first_node("SceneSettings");

	//string toFill = "1"; 
	//string* toWrite = &toFill; //teoricament el string este tiene que existir mientras el documento exista para que se grabe bien.
	if (difficulty == 1) {
		xml_attribute<> *attr1 = doc.allocate_attribute("initSpeedMultiplier",toWrite->c_str());
		root_node->append_attribute(attr1);
		//xml_attribute<> *attr2 = doc.allocate_attribute("vides", "10000");
		//root_node->append_attribute(attr2);
		//xml_attribute<> *attr3 = doc.allocate_attribute("timeDivision", "1");
		//root_node->append_attribute(attr3);
	}
	if (difficulty == 2) {
		xml_attribute<> *attr1 = doc.allocate_attribute("initSpeedMultiplier", "2");
		root_node->append_attribute(attr1);
		xml_attribute<> *attr2 = doc.allocate_attribute("vides", "5000");
		root_node->append_attribute(attr2);
		xml_attribute<> *attr3 = doc.allocate_attribute("timeDivision", "1.5");
		root_node->append_attribute(attr3);
	}
	if (difficulty == 3) {
		xml_attribute<> *attr1 = doc.allocate_attribute("initSpeedMultiplier", "3");
		root_node->append_attribute(attr1);
		xml_attribute<> *attr2 = doc.allocate_attribute("vides", "1000");
		root_node->append_attribute(attr2);
		xml_attribute<> *attr3 = doc.allocate_attribute("timeDivision", "2.5");
		root_node->append_attribute(attr3);
	}
	
	
	cout << "I wrote : " << endl;
	cout << root_node->first_attribute("initSpeedMultiplier")->value() << endl;/*
	cout << root_node->first_attribute("vides")->value() << endl;
	cout << root_node->first_attribute("timeDivision")->value() << endl;
	
}*/
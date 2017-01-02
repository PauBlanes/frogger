/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"


#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <XML/rapidxml.hpp>
using namespace rapidxml;
using namespace std;
using namespace Logger;

namespace IOManager {

	// Base test function for XML purposes (TODO) -> Ho he intentat però no hi ha manera, a més nose molt bé que retornar perque no em deixa retornar un vector ni un node.
	std::vector<string> ReadXML(string &&filename, string difficulty) {
		std::vector<string> info;

		cout << "Llegint les dades del nivell..." << endl;

		xml_document<> doc;
		xml_node<> * root_node;
		//Read the xml file into a vector
		ifstream theFile(filename);

		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');

		// Parse the buffer using the xml file parsing library into doc 
		doc.parse<0>(&buffer[0]);
		// Find our root node
		root_node = doc.first_node("SceneSettings");

		xml_node<> *nodeToRead = root_node->first_node(difficulty.c_str());

		string temp1 = nodeToRead->first_attribute("initSpeedMultiplier")->value();
		string temp2 = nodeToRead->first_attribute("vides")->value();
		string temp3 = nodeToRead->first_attribute("timeDivision")->value();

		info.emplace_back(temp1);
		info.emplace_back(temp2);
		info.emplace_back(temp3);

		return info;
	}
	/*
	// Loader function that takes level info for a grid
	std::vector<std::vector<ObjectID>> LoadLevel(std::string &&filename, int &rows, int &cols) {
		std::ifstream fileData(RESOURCE_FILE(filename));
		ASSERT(fileData.good());
		std::vector<std::vector<ObjectID>> lvlData;
		std::string line;
		while (std::getline(fileData, line)) {
			std::istringstream strData(std::move(line));
			lvlData.emplace_back(std::istream_iterator<ObjectID>(std::move(strData)), std::istream_iterator<ObjectID>());
		}
		rows = int(lvlData.size()); cols = int(lvlData[0].size());
		fileData.close();
		#pragma region DEBUG_DATA
			Println("Level: ", filename);
			for (auto &r : lvlData) {
				for (auto &c : r) Print(c, ' ');
				Endln();
			}
		#pragma endregion
		return std::move(lvlData);
	}*/

}
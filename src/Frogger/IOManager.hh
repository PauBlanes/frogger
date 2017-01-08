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

#include "RankingsScene.hh"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include <XML/rapidxml.hpp>
using namespace rapidxml;
using namespace std;
using namespace Logger;

namespace IOManager {

	//Llegir un fitxer xml
	vector<string> ReadXML(string &&, string );
	//Escriure a un fitxer binari
	void WriteBin(const string &,string&, vector<userRank>, int);
	//Llegir d'un fitxer binari
	vector <userRank> ReadBin(const string &, string&);
	
}
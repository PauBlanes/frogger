#include "IOManager.hh"

vector<string> IOManager::ReadXML(string &&filename, string difficulty) {
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

void IOManager::WriteBin(const string &filename, userRank u1) {

	ofstream fsalida(filename, ios::out | ios::binary ||ios::app); //obrim un archiu per escriure en binari i de tipo append per poder escriure al final i no xafar-ho tot cada cop
	userRank temp = u1;
	if (fsalida.is_open())
	{
		
		fsalida.write(reinterpret_cast<char*>(&temp), sizeof(temp));				
		fsalida.close();
		
		ifstream fentrada(filename, ios::in | ios::binary | ios::app);
		userRank tempUser;
		cout << u1.score << endl;
		fentrada.read(reinterpret_cast<char*>(&u1), sizeof(u1));
		cout << u1.userName << ": " << u1.score << endl;
		fentrada.close();
	}
	else cout << "Unable to open file for writing\n";

}

vector<userRank> IOManager::ReadBin(const string &filename) {
	
	ifstream fentrada(filename, ios::in | ios::binary |ios::app); //ate per posarnos al final del archiu i tenir el tamany
	
	if (fentrada.is_open())
	{
		
		vector<userRank>bestPlayers;
		//int i = 0;
		//while (i <3) {
					
			
			userRank tempUser;
			fentrada.read(reinterpret_cast<char*>(&tempUser), sizeof(tempUser));
			bestPlayers.push_back(tempUser);
			
			cout << bestPlayers[0].userName << ": " << bestPlayers[0].score << endl;
			
			//cout << fentrada.tellg() << endl;
			
			//i++;	

		//}
		
		fentrada.close();
		
		return bestPlayers;
		
	}
	else cout << "Unable to open file for reading\n";	
	
}
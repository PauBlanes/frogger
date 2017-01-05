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

void IOManager::WriteBin(const string &filename, vector<userRank> highScorers, int rankPos) {

	//int posToInsert = sizeof(userRank) * (rankPos - 1); //la posicio del fitxer on anirà la nova informacio
	
	ofstream fsalida(filename, ios::out | ios::binary); //obrim un archiu per escriure en binari ens posem al final per comprovar si hem d'insertar al final
	//fsalida.seekp(posToInsert); //ens movem a on volem insertar per no haver de reescriure tot el fitxer sencer cada cop, nomes a partir de la posicio que volem insertar
	
	if (fsalida.is_open())
	{
		for (int i = 0; i < highScorers.size();i++) {
			fsalida.write(reinterpret_cast<char*>(&highScorers[i]), sizeof(highScorers[i]));
		
		}
		
		fsalida.close();	  
		
	}else cout << "Unable to open file for writing\n";
}
	
vector<userRank> IOManager::ReadBin(const string &filename) {
	
	ifstream fentrada(filename, ios::in | ios::binary); 
	
	if (fentrada.is_open())
	{
		
		vector<userRank>bestPlayers;

		userRank tempUser;
		for (int i = 0; fentrada.read(reinterpret_cast<char*>(&tempUser), sizeof(tempUser)); i++) {			
			bestPlayers.push_back(tempUser);
						
		}
		
		fentrada.close();
		
		return bestPlayers;
		
	}
	else cout << "Unable to open file for reading\n";	
	
}
#include "IOManager.hh"

std::vector<string> IOManager::ReadXML(string &&filename, string difficulty) {
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

void IOManager::WriteBin(const string &filename, string userName, int score) {

	char const*newEntry;
	userName.append(to_string(score)); //ajuntem el nom i el numero

	ofstream file(filename, ios::out | ios::binary); //obrim un archiu per escriure en binari i de tipo append per poder escriure al final i no xafar-ho tot cada cop

	if (file.is_open())
	{

		newEntry = new char[userName.size()];
		newEntry = userName.c_str(); //convertim a char* perque es el que ens demana el write.
		file.write(newEntry, sizeof(newEntry));
		file.close();
	}
	else cout << "Unable to open file for writing\n";

}

string IOManager::ReadBin(const string &filename) {
	
	streampos size;
	char * memblock;
	string temp;

	ifstream file(filename, ios::in | ios::binary | ios::ate); //ate per posarnos al final del archiu i tenir el tamany
	if (file.is_open())
	{

		size = file.tellg(); //amb aixo tindrem el tamany del archiu pq estem a la ultima posicio.
		memblock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();
		for (int i = 0; i < size;i++) {
			char c = static_cast<char>(std::bitset<6>(memblock[i]).to_ulong() + 64);
			temp += c;
		}		

		delete[] memblock;
	}
	else cout << "Unable to open file for reading\n";

	return temp;
	
}
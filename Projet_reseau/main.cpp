#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "TrameList.h"
#include "fonctionsMaths.h"

using namespace std;

int main() {

	std::string test = "";
	int Flags = 0x1675;
	std::stringstream stream;

	stream << std::hex << setw(3) << setfill('0') << Flags << "\n je suis une pepite de chocolat \n";

	test = stream.str();
	std::cout << test;
	


	ifstream f("analyse_donnee.txt"); //Ouverture fichier en lecture seule
	string trame;

	trame = fonctionsMaths::getByteFile(&f, trame);
	TrameList EthList = TrameList(trame);
	EthList.afficherListe();
	return 0;
}

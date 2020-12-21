#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "TrameList.h"
#include "fonctionsMaths.h"

using namespace std;

int main() {

	std::string test = "";
	int Flags = 16;
	//test = std::string(test) + (setw(3) << setfill('0') << Flags) ;

	std::cout << test;

	ifstream f("analyse_donnee.txt"); //Ouverture fichier en lecture seule
	string trame;

	trame = fonctionsMaths::getByteFile(&f, trame);
	TrameList EthList = TrameList(trame);
	EthList.afficherListe();
	return 0;
}

#include <iostream>
#include <string>
#include <fstream>

#include "TrameList.h"
#include "fonctionsMaths.h"

using namespace std;

int main() {
	ifstream f("analyse_donnee.txt"); //Ouverture fichier en lecture seule
	string trame;
	
	trame = fonctionsMaths::getByteFile(&f, trame);
	TrameList EthList = TrameList(trame);
	//EthList.afficherListe();
	return 0;
}

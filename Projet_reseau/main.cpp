#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "TrameList.h"
#include "fonctionsMaths.h"

using namespace std;

int main() {

	ifstream f("analyse_donnee.txt"); //Ouverture fichier en lecture seule
	string trame;

	trame = fonctionsMaths::getByteFile(&f, trame);
	TrameList EthList = TrameList(trame);
	EthList.afficherListe();
	EthList.ecrireListe("Resultat.txt");
	return 0;
}

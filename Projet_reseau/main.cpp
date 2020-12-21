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
	TrameList EthList = TrameList(fonctionsMaths::getByteFile(&f, std::string()));
	EthList.afficherListe();
	//EthList.ecrireListe("Resultat.txt"); //Creation d'un fichier texte avec les details des trames dessus
	return 0;
}

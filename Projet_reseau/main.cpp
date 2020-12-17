#include <iostream>
#include <string>
#include <fstream>
#include "Trame.h"
#include "IpFrame.h"
#include "fonctionsMaths.h"
using namespace std;

int main() {
	Trame Eth;
	ifstream f("analyse_donnee.txt"); //Ouverture fichier en lecture seule
	string ligne;
	string chaine;
	//string test = "ffff";
	//int res = fonctionsMaths::hexToDec(test, 4);
	//std::cout << res << endl;
	while (f) {
		ligne = fonctionsMaths::getByteLine(&f);
		chaine.append(ligne);
		
	}
	std::cout << chaine << '\n';
	Eth.construireTrame(chaine);
	Eth.afficherTrame();
	

	return 0;
}
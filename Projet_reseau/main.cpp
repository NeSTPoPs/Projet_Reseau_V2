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
	string trame;
	//string test = "ffff";
	//int res = fonctionsMaths::hexToDec(test, 4);
	//std::cout << res << endl;
/* while (f) {
		ligne = fonctionsMaths::getByteLine(&f);
		chaine.append(ligne);

	} */
	trame = fonctionsMaths::getByteFile(&f, trame);
	
	//std::cout << chaine << '\n';
	Eth.construireTrame(trame);
	Eth.afficherTrame();


	return 0;
}

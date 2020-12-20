#ifndef DEF_FONCTIONSMATHS
#define DEF_FONCTIONSMATHS

#include <string.h>
#include <string>
#include <stdlib.h>
#include <fstream>

class fonctionsMaths
{
public:

	static int est_hexadecimal(char c);
	/* retourne 1 si c est un caractere hexadecimal, 0 sinon*/

	static int hexToDec(std::string n,int taille);
	/* Convertit une chaine de caract�re de taille 'taille' en hexadecimal vers decimal*/


	static std::string getByteLine(std::string line, int *countOffset);
	/* Lit une ligne du fichier f de maniere a retourner une chaine de caractere hexadecimal sans espace de maximum 16 octets (32 caracteres)*/

	static std::string getByteFile(std::ifstream* f, std::string chaine);
	/* Lit le fichier f passé en parametre avec les appels de la fonction getByteLine */

	static char* getProtocolName(int type, char *p);
	static char* getIcmpType(int protocol, char* p);
	/* modifie la chaine de caractere p
	ces fonctions servent a obtenir une chaine de caractere indiquant le nom du protocol/type
	lors de l'appel de cette fonctions, on utilise un pointeur char *p deja declare pour le modifier
	Ces fonctions retourne le pointeur p */

	static void afficheMacAdress(int mac[6]);
	static void afficheIpAdress(int ip[4]);
	/* affiche correctement des addresses mac et IP avec des points */

	static unsigned int length(char* chaine);

};

#endif

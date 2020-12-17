#ifndef DEF_FONCTIONSMATHS
#define DEF_FONCTIONSMATHS

#include <string>
#include <fstream>
class fonctionsMaths
{
public:
	static unsigned long hexToDec(std::string n,int taille); 
	/* Convertie une chaine de caractère de taille 'taille' en hexadecimal vers decimal*/
	static std::string getByteLine(std::ifstream *f);
	/* Lis une ligne du fichier f de maniere a retourner une chaine de caractere hexadecimal sans espace de maximum 16 octets (32 caracteres)*/
	static char* getProtocolName(int protocol, char *p);
	/* modifie la chaine de caractere p
	cette fonction sert a obtenir une chaine de caractere indiquant le nom du protocol
	lors de l'appel de cette fonctions, on utilise un pointeur char *p deja declare pour le modifier 
	Cette fonction retourne le pointeur p */
	static void afficheMacAdress(int mac[6]);
	static void afficheIpAdress(int ip[4]);
};

#endif

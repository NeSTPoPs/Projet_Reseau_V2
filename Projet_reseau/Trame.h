#ifndef DEF_TRAME
#define DEF_TRAME

#include <string>
#include "fonctionsMaths.h"
#include "IpFrame.h"

/*Cette classe contient TOUTE les informations de la trame. Elle contient explicitement les donnés de la trame Ethernet
* et met le reste dans le champ 'data'. Data est une classe mère pour les classes IpFrame, TCP, DHCP , ... */

class Trame
{
public:
	Trame(); // Constructeur utilisé pour le debogage
	Trame(std::string t); // Constructeur qui sera utilisé pour lire une trame. 't' est toute la chaine de la trame.
	Data getData();
	int* getDestAdd();
	int* getSrcAdd();
	
	void newDestAdd(int ip[6]);
	void newSrcAdd(int ip[6]);
	void newData(Data *d);
	void afficherTrame();

	void construireTrame(std::string chaine);

private:
	int destAdd[6];
	int srcAdd[6];
	int type;
	Data *d;
};

#endif
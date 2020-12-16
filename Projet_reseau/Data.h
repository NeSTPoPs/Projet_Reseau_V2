#ifndef DEF_DATA
#define DEF_DATA

#include "fonctionsMaths.h"
#include <string>
class Data
{
protected:
	void newType(std::string type);

public:
	Data();
	Data(std::string type);
	std::string getType();
	std::string lire();
	virtual void afficherData();
	void construireData(char chaine[], int type);
private:
	std::string type; //Je vais surement retirer ça ...
};

#endif
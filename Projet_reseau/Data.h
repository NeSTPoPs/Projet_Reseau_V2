#ifndef DEF_DATA
#define DEF_DATA

#include "fonctionsMaths.h"

class Data
{
protected:
	void newType(std::string type);

public:
	Data();
	virtual ~Data();
	Data(std::string type);
	std::string getType();
	std::string lire();
	virtual void afficherData();
	virtual void afficherData(const int tabulation);
	void construireData(char chaine[]);
private:
	std::string type;
};

#endif
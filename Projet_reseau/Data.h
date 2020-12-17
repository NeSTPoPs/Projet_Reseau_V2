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
	~Data();
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
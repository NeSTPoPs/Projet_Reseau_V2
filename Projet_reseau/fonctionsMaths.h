#ifndef DEF_FONCTIONSMATHS
#define DEF_FONCTIONSMATHS

#include <string>
#include <fstream>
class fonctionsMaths //Test
{
public:
	static unsigned long hexToDec(std::string n,int taille);
	static std::string getByteLine(std::ifstream *f);
private:
	int n;
};

#endif
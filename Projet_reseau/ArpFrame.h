#ifndef DEF_ARPFRAME
#define DEF_ARPFRAME

#include "Data.h"

class ArpFrame : public Data
{
public:
	ArpFrame();
	ArpFrame(char* chaine);
	~ArpFrame();
	void construireData(char chaine[]);
	void afficherData(const int tabulation);
private:
	int hardware;
	int protocol;
	int hLen;
	int pLen;
	int operation;
	int senderHA[6];
	int senderIA[4];
	int targetHA[6];
	int targetIA[4];
};

#endif

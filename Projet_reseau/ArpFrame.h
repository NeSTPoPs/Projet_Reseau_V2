#ifndef DEF_ARPFRAME
#define DEF_ARPFRAME

#include "Data.h";

class ArpFrame : public Data
{
public:
	ArpFrame();
	ArpFrame(char* chaine, int type);
	~ArpFrame();
	void construireData(char chaine[], int type);
	void afficherData(const int tabulation);
private:
	int hardware;
	int protocol;
	int hLen;
	int pLen;
	int operation;
	int senderHA;
	int senderIA;
	int targetHA;
	int targetIA;
};

#endif

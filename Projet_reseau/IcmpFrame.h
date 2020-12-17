#pragma once
#include "Data.h"
class IcmpFrame : public Data
{
public:
	IcmpFrame();
	IcmpFrame(char* chaine);
	~IcmpFrame();

	void construireData(char chaine[]);
	void afficherData(const int tabulation);

private:
	int type;
	int code;
	int checksum;
	int identifier;
	int seqNum;
	char* opData;
};


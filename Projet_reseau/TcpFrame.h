#pragma once
#include "Data.h"
class TcpFrame : public Data
{
public:
	TcpFrame();
	TcpFrame(char* chaine);
	~TcpFrame();

	void construireData(char chaine[]);
	void afficherData(const int tabulation);

private:
	int srcPort;
	int destPort;
	unsigned long int seqNum;
	unsigned long int ackNum;
	int dataOffset;
	int reserved;
	int URG;
	int ACK;
	int PSH;
	int RST;
	int SYN;
	int FIN;
	int window;
	int checksum;
	int urgentPointer;
	char options[16];
	char Data[64];
};


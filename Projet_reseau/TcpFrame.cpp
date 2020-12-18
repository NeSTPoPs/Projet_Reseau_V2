#include "TcpFrame.h"

TcpFrame::TcpFrame()
{
	srcPort = -1;
	destPort = -1;
	seqNum = -1;
	ackNum = -1;
	dataOffset = -1;
	reserved = -1;
	URG = -1;
	ACK = -1;
	PSH = -1;
	RST = -1;
	SYN = -1;
	FIN = -1;
	window = -1;
	checksum = -1;
	urgentPointer = -1;
	for (int j = 0; j < 16; j++) {
		options[j] = ' ';
	}
	for (int i = 0; i < 63; i++)
		Data[i] = ' ';
	Data[63] = '\0';
}

TcpFrame::TcpFrame(char* chaine)
{
	*this = TcpFrame();
	this->construireData(chaine);
}

TcpFrame::~TcpFrame()
{

}

void TcpFrame::construireData(char chaine[])
{
	int lecture;
	this->srcPort = fonctionsMaths::hexToDec(&(chaine[0]), 4);
	this->destPort = fonctionsMaths::hexToDec(&(chaine[4]), 4);
	this->seqNum = fonctionsMaths::hexToDec(&(chaine[8]), 8);
	this->ackNum = fonctionsMaths::hexToDec(&(chaine[16]), 8);
	this->dataOffset = fonctionsMaths::hexToDec(&(chaine[24]), 1);
	lecture = fonctionsMaths::hexToDec(&(chaine[25]), 3);
	this->window = fonctionsMaths::hexToDec(&(chaine[28]), 4);
	this->checksum = fonctionsMaths::hexToDec(&(chaine[32]), 4);
	this->urgentPointer = fonctionsMaths::hexToDec(&(chaine[36]), 4);
	int i = 40;
	int j = 0;
	while ( fonctionsMaths::est_hexadecimal(chaine[i]) ) {
		this->Data[j] = chaine[i];
		j++;
		i++;
	}

}

void TcpFrame::afficherData(const int tabulation)
{

}

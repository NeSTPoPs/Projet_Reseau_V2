#include "ArpFrame.h"

ArpFrame::ArpFrame()
{
	this->newType("ARP");
	hardware = 0;
	protocol = 0;
	hLen = 0;
	pLen = 0;
	operation = 0;
	senderHA = 0;
	senderIA = 0;
	targetHA = 0;
	targetIA = 0;
}

ArpFrame::ArpFrame(char* chaine, int type)
{
	*this = ArpFrame();
	this->construireData(chaine, type);
}

ArpFrame::~ArpFrame()
{
}

void ArpFrame::construireData(char chaine[], int type)
{
}

void ArpFrame::afficherData(const int tabulation)
{
}

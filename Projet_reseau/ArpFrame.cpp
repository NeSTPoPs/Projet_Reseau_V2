#include "ArpFrame.h"

ArpFrame::ArpFrame()
{
	this->newType("ARP");
	hardware = 0;
	protocol = 0;
	hLen = 0;
	pLen = 0;
	operation = 0;
	for (int i = 0; i < 6; i++) {
		senderHA[i] = 0;
		targetHA[i] = 0;
	}
	for (int j = 0; j < 4; j++) {
		senderIA[j] = 0;
		targetIA[j] = 0;
	}
}

ArpFrame::ArpFrame(char* chaine)
{
	*this = ArpFrame();
	this->construireData(chaine);
}

ArpFrame::~ArpFrame()
{
}

void ArpFrame::construireData(char chaine[])
{
	this->hardware = fonctionsMaths::hexToDec(&(chaine[0]), 4);
	this->protocol = fonctionsMaths::hexToDec(&(chaine[4]), 4);
	this->hLen = fonctionsMaths::hexToDec(&(chaine[8]), 2);
	this->pLen = fonctionsMaths::hexToDec(&(chaine[10]), 2);
	this->operation = fonctionsMaths::hexToDec(&(chaine[12]), 4);

	for (int i = 0; i < 6; i++) {
		this->senderHA[i] = fonctionsMaths::hexToDec(&(chaine[16+(i*2)]), 2);
		this->targetHA[i] = fonctionsMaths::hexToDec(&(chaine[36+(i*2)]), 2);
	}
	for (int j = 0; j < 4; j++) {
		this->senderIA[j] = fonctionsMaths::hexToDec(&(chaine[28 + (j*2)]), 2);
		this->targetIA[j] = fonctionsMaths::hexToDec(&(chaine[48 + (j*2)]), 2);
	}

}

void ArpFrame::afficherData(const int tabulation)
{
	char tab[5];
	for (int i = 0; i < tabulation; i++) {
		tab[i] = '\t';
	}
	tab[tabulation] = '\0';
	char protocolName[50];
	fonctionsMaths::getProtocolName(this->protocol, protocolName);

	printf("%s==== ARP ====\n", tab);
	printf("%sHardware type: %i\n", tab, this->hardware);
	printf("%sProtocol type: %.4x (%s)\n", tab, this->protocol, protocolName);
	printf("%sHardware size: %i\n", tab, this->hLen);
	printf("%sProtocol size: %i\n", tab, this->pLen);
	printf("%sOpcode: %i\n", tab, this->operation);
	printf("%sSender MAC address: ",tab);
	fonctionsMaths::afficheMacAdress(this->senderHA);
	printf("\n%sSender IP address: ", tab);
	fonctionsMaths::afficheIpAdress(this->senderIA);
	printf("\n%sTarget MAC address: ", tab);
	fonctionsMaths::afficheMacAdress(this->targetHA);
	printf("\n%sTarget IP address: ", tab);
	fonctionsMaths::afficheIpAdress(this->targetIA);
	printf("\n");
	return;
}

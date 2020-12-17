#include "IpFrame.h"
#include <iostream>

IpFrame::IpFrame() {
	this->newType("IP");
	version = 0;
	ihl = 0;
	tos = 0;
	totalLength = 0;
	identification = 0;
	flags = 0;
	fragmentOffset = 0;
	ttl = 0;
	protocol = 0;
	headerChecksum = 0;
	options = 0;
	for (int i = 0; i < 4; i++) {
		destAdd[i] = 0;
		srcAdd[i] = 0;
	}
	d = NULL;
}

IpFrame::~IpFrame()
{
}

std::string IpFrame::lire()
{

	return std::string();
}

const char * IpFrame::strProtocol()
{
	switch (this->protocol) {
	case 1:
		//Protocol ICMP
		return "ICMP";
		break;

	default:
		return "Protocol non reconnu";
		break;
	}
	return "Protocol non reconnu";
}

void IpFrame::afficherData(int tabulation) {
	char tab[5];
	for (int i = 0; i < tabulation; i++) {
		tab[i] = '\t';
	}
	tab[tabulation] = '\0';

	printf("%s====Datagramme IP====\n",tab);
	printf("%sVersion: %x\n",tab, this->version);
	printf("%sIHL: %x\n", tab, this->ihl);
	printf("%sTOS: %x\n", tab, this->tos);
	printf("%sTotal length: %i octets (0x%.4x)\n", tab, this->totalLength, this->totalLength);
	printf("%sIdentification :%x\n", tab, this->identification);
	printf("%sFlags :%x\n", tab, this->flags);
	printf("%sFragment offset :%x\n", tab, this->fragmentOffset);
	printf("%sTTL :%x\n", tab, this->ttl);
	printf("%sProtocol :%x (%s)\n", tab, this->protocol, this->strProtocol());
	printf("%sHeader Checksum :%x\n", tab, this->headerChecksum);
	printf("%sSource IP Address : ", tab);
	printf("%i", this->srcAdd[0]);
	for (int i = 1; i < 4; i++) {
		printf(".%i", this->srcAdd[i]);
	}
	printf("\n%sDestination IP Address : ", tab);
	printf("%i", this->destAdd[0]);
	for (int i = 1; i < 4; i++) {
		printf(".%i", this->destAdd[i]);
	}
	return;
}

void IpFrame::construireData(char chaine[], int type)
{
	int lecture;
	this->version = fonctionsMaths::hexToDec(&(chaine[0]), 1);
	this->ihl = fonctionsMaths::hexToDec(&(chaine[1]), 1);
	this->tos = fonctionsMaths::hexToDec(&(chaine[2]), 2);
	this->totalLength = fonctionsMaths::hexToDec(&(chaine[4]), 4);
	this->identification = fonctionsMaths::hexToDec(&(chaine[8]), 4);
	
	/* Flags etant sur 3 bits , on lit un caractère codé sur 4 bits (noté lecture)
	puis on extrait le bit de droite (qui vaut lecture % 2)*/
	lecture = fonctionsMaths::hexToDec(&(chaine[12]), 1);
	this->flags = lecture - (lecture % 2); 
	this->fragmentOffset = fonctionsMaths::hexToDec(&(chaine[13]), 3) + (lecture % 2) * 4096; //On ajoute le bit manquant
	this->ttl = fonctionsMaths::hexToDec(&(chaine[16]), 2);
	this->protocol = fonctionsMaths::hexToDec(&(chaine[18]), 2);
	this->headerChecksum = fonctionsMaths::hexToDec(&(chaine[20]), 4);
	for (int i = 0; i < 4; i++) {
		this->srcAdd[i] = fonctionsMaths::hexToDec(&(chaine[24 + (i*2)]), 2);
		this->destAdd[i] = fonctionsMaths::hexToDec(&(chaine[32 + (i*2)]), 2);
	}
}

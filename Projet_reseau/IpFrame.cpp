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

std::string IpFrame::lire()
{

	return std::string();
}

void IpFrame::afficherData() {
	printf("====Datagramme IP====\n");
	printf("Version: %x\n", this->version);
	printf("IHL: %x\n", this->ihl);
	printf("TOS: %x\n", this->tos);
	printf("Total length: %i octets (0x%.4x)\n", this->totalLength, this->totalLength);
	printf("Identification :%x\n", this->identification);
	printf("Flags :%x\n", this->flags);
	printf("Fragment offset :%x\n", this->fragmentOffset);
	printf("TTL :%x\n", this->ttl);
	printf("Protocol :%x\n", this->protocol);
	printf("Header Checksum :%x\n", this->headerChecksum);
	std::cout << "Source IP Address : ";
	printf("%i", this->srcAdd[0]);
	for (int i = 1; i < 4; i++) {
		printf(".%i", this->srcAdd[i]);
	}
	std::cout << "\nDestination IP Address : ";
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

#include "Trame.h"

#include <iostream>

Trame::Trame() {
	for (int i = 0; i < 6; i++) {
		srcAdd[i] = 0;
		destAdd[i] = 0;
	}
	this->type = 0;
	this->d = NULL;
}

Trame::Trame(std::string t)
{
	for (int i = 0; i < 6; i++) {
		srcAdd[i] = 0;
		destAdd[i] = 0;
	}
	this->type = 0;
	this->d = NULL;
}

Trame::~Trame()
{
}

void Trame::newDestAdd(int ip[6]) {
	for (int i = 0; i < 6; i++) {
		this->destAdd[i] = ip[i];
	}
	return;
}

void Trame::newSrcAdd(int ip[6]) {
	for (int i = 0; i < 6; i++) {
		this->srcAdd[i] = ip[i];
	}
	return;
}

void Trame::newData(Data *d) {
	this->d = d;
}

void Trame::afficherTrame()
{
	std::cout << "===Ethernet===\n";
	std::cout << "Source MAC Address : ";
	for (int i = 0; i < 5; i++) {
		printf("%x.", this->srcAdd[i]);
	}
	printf("%x\n", this->srcAdd[5]);

	std::cout << "Destination MAC Address : ";
	for (int i = 0; i < 5; i++) {
		printf("%x.", this->destAdd[i]);
	}
	printf("%x\n", this->destAdd[5]);
	printf("Type:%04x", this->type);
	char protocolName[50];
	fonctionsMaths::getProtocolName(this->type, protocolName);
	printf(" (%s)\n", protocolName);
	IpFrame* piF;
	ArpFrame* paF;
	
	switch (this->type) {
	case 0x800:
		piF = (IpFrame*)this->d;
		piF->afficherData(1);
		break;
	case 0x806:
		paF = (ArpFrame*)this->d;
		paF->afficherData(1);
		break;
	default:
		//Protocol non reconnu
		printf(" (Protocol non reconnu)\n");
		return;
	}
	return;
}

void Trame::construireTrame(std::string chaine)
{
	/* Comment ça marche ?
	On part d'une chaine déjà décodé et sans erreurs, en hexadecimal, sans espace, sans préambule.
	On lit les 14 premiers octets (28 premiers caracteres) puis on place le reste dans l'attribut d (Data) puis on appelle la fonction de decodage lié à Data
	*/
	int dest[6];
	int src[6];
	for (int i = 0; i < 6; i++) {
		dest[i] = fonctionsMaths::hexToDec(&(chaine[(i*2)]), 2);
		src[i] = fonctionsMaths::hexToDec(&(chaine[(i*2) + 12]), 2);
	}
	this->type = fonctionsMaths::hexToDec(&(chaine[24]), 4);
	this->newDestAdd(dest);
	this->newSrcAdd(src);
	if (this->type == 0x800)
	{
		IpFrame *iF = new IpFrame(&(chaine[28]), this->type);
		this->d = iF;
	}
}

Data Trame::getData() {
	return *d;
}

int *Trame::getDestAdd()
{
	return destAdd;
}

int *Trame::getSrcAdd()
{
	return srcAdd;
}

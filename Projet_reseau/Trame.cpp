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
	if (this->d)
		delete this->d;
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
	if (this == NULL) {
		std::cout << "ERREUR FONCTION 'afficherTrame()' : pointeur null\n";
		return;
	}
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
		piF = (IpFrame*)this->d; //On cast le Data comme etant un IpFrame pour avoir la bonne fonction afficherData
		piF->afficherData(1);
		break;
	case 0x806:
		paF = (ArpFrame*)this->d; //On cast le Data comme etant un ArpFrame pour avoir la bonne fonction afficherData
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
	
	if (chaine.length() < 28) {
		std::cout << "Impossible de creer une trame Ethernet : la trame donnee est trop courte\n";
		return ;
	}
	/* Comment �a marche ?
	On part d'une chaine d�j� d�cod� et sans erreurs, en hexadecimal, sans espace, sans pr�ambule.
	On lit les 14 premiers octets (28 premiers caracteres) puis on place le reste dans l'attribut d (Data) puis on appelle la fonction de decodage li� � Data
	*/
	for (int i = 0; i < 6; i++) {
		this->destAdd[i] = (int) fonctionsMaths::hexToDec(&(chaine[(((double)i)*2)]), 2);
		this->srcAdd[i] = (int) fonctionsMaths::hexToDec(&(chaine[(((double)i) *2) + 12]), 2);
	}
	this->type = fonctionsMaths::hexToDec(&(chaine[24]), 4);
	IpFrame* iF;
	ArpFrame* aF;
	switch (this->type) {
	case 0x800:
		iF = new IpFrame(&(chaine[28]));
		this->d = iF;
		break;
	case 0x806:
		aF = new ArpFrame(&(chaine[28]));
		this->d = aF;
		break;
	default:
		break;
	}
	return;
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

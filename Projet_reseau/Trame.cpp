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
	if (this->d) {
		switch (this->type) {
		case 0x800://IpFrame
			delete ((IpFrame *)this->d);
			break;
		case 0x806://ArpFrame
			delete ((ArpFrame *)this->d);
			break;
		default:
			break;
		}
	}
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
	std::cout << this->toString();
	return;
}

std::string Trame::toString() {
	if (this == NULL)
		return "ERREUR FONCTION 'afficherTrame()' : pointeur null";
	char protocolName[50];
	std::stringstream s;
	std::string res = "";

	fonctionsMaths::getProtocolName(this->type, protocolName);

	res = res + "===Ethernet===\n";
	res = res + "Source MAC Address: " + fonctionsMaths::toStringMacAdress(this->srcAdd) + "\n";
	res = res + "Destination MAC Address: " + fonctionsMaths::toStringMacAdress(this->destAdd) + "\n";
	s << std::hex << std::setw(4) << std::setfill('0') << this->type;
	res = res + "Type: 0x" + s.str() + " (" + std::string(protocolName) + ")\n";

	switch (this->type) {
	case 0x800:
		return res + ((IpFrame*)this->d)->toString(1); //On cast le Data comme etant un IpFrame pour avoir la bonne fonction afficherData
		break;
	case 0x806:
		return res + ((ArpFrame*)this->d)->toString(1); //On cast le Data comme etant un ArpFrame pour avoir la bonne fonction afficherData
		break;
	default:
		//Protocol non reconnu
		res = res + "(Protocol non reconnu)\n";
	}
	return res + this->d->toString(1);
}

void Trame::construireTrame(std::string chaine)
{
	
	if (chaine.length() < 28) {
		std::cout << "Impossible de creer une trame Ethernet : la trame donnee est trop courte\n";
		return ;
	}
	/* Comment ça marche ?
	On part d'une chaine déjà décodé et sans erreurs, en hexadecimal, sans espace, sans préambule.
	On lit les 14 premiers octets (28 premiers caracteres) puis on place le reste dans l'attribut d (Data) puis on appelle la fonction de decodage lié à Data
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

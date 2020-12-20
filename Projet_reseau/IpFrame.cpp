#include "IpFrame.h"
#include <iostream>

IpFrame::IpFrame() {
	this->newType("DoD Internet(Datagramme IP)");
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

IpFrame::IpFrame(char* chaine)
{
	*this = IpFrame();
	this->construireData(chaine);
}

IpFrame::~IpFrame()
{
	if (this->d)
		delete this->d;
}

std::string IpFrame::lire()
{

	return std::string();
}

void IpFrame::afficherData(int tabulation) {
	char tab[5];
	for (int i = 0; i < tabulation; i++) {
		tab[i] = '\t';
	}
	tab[tabulation] = '\0';
	char protocolName[50];

	printf("%s====Datagramme IP====\n", tab);
	printf("%sVersion: %x\n", tab, this->version);
	printf("%sIHL: %x\n", tab, this->ihl);
	printf("%sTOS: %x\n", tab, this->tos);
	printf("%sTotal length: %i octets\n", tab, this->totalLength);
	printf("%sIdentification : 0x%x (%i)\n", tab, this->identification, this->identification);
	printf("%sFlags : 0x%.4x\n", tab, this->flags);
	printf("%sFragment offset : %i\n", tab, this->fragmentOffset);
	printf("%sTime to live : %i\n", tab, this->ttl);
	fonctionsMaths::getProtocolName(this->protocol, protocolName);
	printf("%sProtocol : %i (%s)\n", tab, this->protocol, protocolName);
	printf("%sHeader Checksum : 0x%x\n", tab, this->headerChecksum);
	printf("%sSource IP Address : ", tab);
	fonctionsMaths::afficheIpAdress(this->srcAdd);
	printf("\n%sDestination IP Address : ", tab);
	fonctionsMaths::afficheIpAdress(this->destAdd);
	printf("\n");
	if (this->d) {
		this->d->afficherData(tabulation+1);
		std::cout << "On affiche les data\n";
	}
	return;
}

void IpFrame::construireData(char chaine[])
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

	
	if (this->protocol == 1) { //Les donnees transporte par la trame IP sont de type ICMP
		int i = 40;
		while ((i + 4 < this->ttl) && not (fonctionsMaths::hexToDec(&(chaine[i]), 4) == 0x0800)) {
			//On recherche le protocole ICMP qui est après les options
			i++;
		}
		if (i + 4 >= this->ttl)
			return;
		this->d = (IcmpFrame*)this->d;
		this->d = new IcmpFrame(&(chaine[i]));
	}
	if (this->protocol == 6) { //Les donnees transporte par la trame IP sont de type TCP
		std::cout << "On construit un tcp\n";
		this->d = (TcpFrame *)this->d;
		this->d = new TcpFrame(&(chaine[40]));
	}
	return;
}

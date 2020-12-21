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

void IpFrame::afficherData(int tabulation) {
	std::cout << this->toString(tabulation);
	return;
}

std::string IpFrame::toString(int tabulation) {
	std::stringstream s;
	std::string tab = std::string(tabulation, '\t');
	std::string res = "";
	char protocolName[50];
	fonctionsMaths::getProtocolName(this->protocol, protocolName);

	res = res + tab + "====Datagramme IP====\n";
	res = res + tab + "Version: " + std::to_string(this->version) + "\n" + tab + "IHL: 0x";

	s << std::hex << std::setw(2) << std::setfill('0') << this->ihl;
	res = res + s.str() + "\n" + tab + "TOS: 0x";
	s.str("");
	s << std::hex << std::setw(2) << std::setfill('0') << this->tos;
	res = res + s.str() + "\n";
	
	res = res + tab + "Total length: " + std::to_string(this->totalLength) + " octets\n";
	s.str("");
	s << std::hex << std::setw(2) << std::setfill('0') << this->identification;

	res = res + tab + "Identification: 0x" + s.str() + " (" + std::to_string(this->identification) + ")\n";
	s.str("");
	s << std::hex << std::setw(4) << std::setfill('0') << this->flags;
	res = res + tab + "Flags: 0x" + s.str() + "\n";
	res = res + tab + "Fragment offset: " + std::to_string(this->fragmentOffset) + "\n";
	res = res + tab + "Time to live: " + std::to_string(this->ttl) + "\n";
	res = res + tab + "Protocol: " + std::to_string(this->protocol) + " (" + std::string(protocolName) + ")\n";

	s.str("");
	s << std::hex << std::setw(4) << std::setfill('0') << this->headerChecksum;

	res = res + tab + "Header checksum: 0x" + s.str() +"\n";
	res = res + tab + "Source IP Address:" + fonctionsMaths::toStringIpAdress(this->srcAdd) + "\n";
	res = res + tab + "Destination IP Address:" + fonctionsMaths::toStringIpAdress(this->destAdd) + "\n";
	if (this->d) {
		if (this->protocol == 1) //ICMP
			return res + ((IcmpFrame *)this->d)->toString(tabulation + 1);
		if (this->protocol == 6) //TCP
			return res + ((TcpFrame*)this->d)->toString(tabulation + 1);
	}
	return res;
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
		this->d = (TcpFrame *)this->d;
		this->d = new TcpFrame(&(chaine[40]));
	}
	return;
}

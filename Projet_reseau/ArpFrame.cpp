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
	std::cout << this->toString(tabulation);
	return;
}

std::string ArpFrame::toString(int tabulation) {
	std::string tableau = std::string(tabulation, '\t');
	std::stringstream stream;
	std::string res;

	res.append(tableau); res.append("=== ARP ===\n");
	res.append(tableau); res.append("Hardware type: "); res.append(std::to_string(this->hardware)); res.append("\n");
	stream << std::hex << std::setw(4) << std::setfill('0') << this->protocol;
	char protocolName[50];
	fonctionsMaths::getProtocolName(this->protocol, protocolName);
	res.append(tableau); res.append("Protocol type: 0x"); res.append(stream.str()); res.append(" "); res.append(protocolName); res.append("\n");
	res.append(tableau); res.append("Hardware size: "); res.append(std::to_string(this->hLen)); res.append("\n");
	res.append(tableau); res.append("Protocol size: "); res.append(std::to_string(this->pLen)); res.append("\n");
	res.append(tableau); res.append("Opcode: "); res.append(std::to_string(this->operation)); res.append("\n");
	res.append(tableau); res.append("Sender MAC address: "); res.append(fonctionsMaths::toStringMacAdress(this->senderHA)); res.append("\n");
	res.append(tableau); res.append("Sender IP address: "); res.append(fonctionsMaths::toStringIpAdress(this->senderIA)); res.append("\n");
	res.append(tableau); res.append("Target MAC address: "); res.append(fonctionsMaths::toStringMacAdress(this->targetHA)); res.append("\n");
	res.append(tableau); res.append("Target IP address: "); res.append(fonctionsMaths::toStringIpAdress(this->targetIA)); res.append("\n");


	return res;
}

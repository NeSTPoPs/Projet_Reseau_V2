#include "IcmpFrame.h"
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
IcmpFrame::IcmpFrame()
{
	this->newType("ICMP");
	type = 0;
	code = 0;
	checksum = 0;
	identifier = 0;
	seqNum = 0;
	for (int i = 0; i < 64; i++)
		opData[i] = '\0';
}

IcmpFrame::IcmpFrame(char* chaine)
{
	*this = IcmpFrame();
	this->construireData(chaine);
}

IcmpFrame::~IcmpFrame()
{
}

void IcmpFrame::construireData(char chaine[])
{
	this->type = fonctionsMaths::hexToDec(&(chaine[0]),2);
	this->code = fonctionsMaths::hexToDec(&(chaine[2]), 2);
	this->checksum = fonctionsMaths::hexToDec(&(chaine[4]), 4);
	this->identifier = fonctionsMaths::hexToDec(&(chaine[8]), 4);
	this->seqNum = fonctionsMaths::hexToDec(&(chaine[12]), 4);
	int i = 16;
	int j = 0;
	while ( fonctionsMaths::est_hexadecimal(chaine[i]) == 1 ) {
		this->opData[j] = chaine[i];
		j++;
		i++;
	}
	this->opData[j] = '\0';
}

void IcmpFrame::afficherData(const int tabulation)
{
	std::cout << this->toString(tabulation);
	return;
}

std::string IcmpFrame::toString(int tabulation) {
	std::stringstream s;
	std::string tab = std::string(tabulation, '\t');
	char typeName[50];

	fonctionsMaths::getIcmpType(this->type, typeName);

	std::string res = tab + "=== ICMP ===\n";
	res = res + tab + "Type: " + std::to_string(this->type) + " (" + std::string(typeName) + ")" + "\n";
	res = res + tab + "Code: " + std::to_string(this->code) + "\n" + tab + "Checksum: 0x";

	s << std::hex << std::setw(4) << std::setfill('0') << this->checksum;
	res.append(s.str()); s.str("");

	s << std::hex << std::setw(4) << std::setfill('0') << this->identifier;
	res = res + "\n" + tab + "Identifier: " + std::to_string(this->identifier) + "(0x" +s.str() +")\n";
	res = res + tab + "Sequence number: " + std::to_string(this->seqNum) + "\n";
	res = res + tab + "Data (" + std::to_string(fonctionsMaths::length(this->opData)/2) + " bytes)\n";

	return res;

}

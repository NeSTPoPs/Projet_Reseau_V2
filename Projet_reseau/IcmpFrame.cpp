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
	std::string tableau = std::string(tabulation, '\t');
	char* tab = new char[tableau.length() + 1];
	strcpy(tab, tableau.c_str());

	char typeName[50];
	fonctionsMaths::getIcmpType(this->type, typeName);

	printf("%s=== ICMP ===\n", tab);
	printf("%sType: %i (%s)\n", tab, this->type, typeName);
	printf("%sCode: %i\n", tab, this->code);
	printf("%sChecksum: 0x%.4x\n", tab, this->checksum);
	printf("%sIdentifier: %i(0x%.4x)\n", tab, this->identifier, this->identifier);
	printf("%sSequence number: %i (0x%.4x)\n", tab, this->seqNum, this->seqNum);
	printf("%sData (%i bytes)\n", tab, fonctionsMaths::length(this->opData) / 2);

}

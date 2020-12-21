#include "Data.h"
#include <string>
#include <iostream>

Data::Data()
{
	type = "";
}

Data::Data(std::string type)
{
	this->type = type;
}

void Data::newType(std::string type)
{
	this->type = type;
	return;
}

std::string Data::getType() {
	return this->type;
}

void Data::construireData(char chaine[])
{

}

std::string Data::toString(int tabulation)
{
	return "Data non reconnu\n";
}

void Data::afficherData()
{
}

void Data::afficherData(int tabulation)
{
}




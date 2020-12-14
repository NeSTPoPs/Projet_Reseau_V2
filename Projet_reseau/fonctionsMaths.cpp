#include "fonctionsMaths.h"
#include <string>
#include <iostream>
#include <fstream>

unsigned long fonctionsMaths::hexToDec(std::string n,int taille)
{
    unsigned long r = 0;
    unsigned long tmp = 0;
    int i = 0;
    for (int i = taille - 1; i >= 0; i = i-1 ){
        if ((n[i] <= 'f' && n[i] >= 'a') || (n[i] <= 'F' && n[i] >= 'A')) {
            if (n[i] <= 'f' && n[i] >= 'a')
                tmp = n[i] - 87;
            else
                tmp = n[i] - 55;
        }
        else {
            if (n[i] <= '9' && n[i] >= '0')
                tmp = n[i] - 48;
            else {
                std::cout << "Erreur convertisseur hexToDec : '" << n[i] << "' n'est pas en hexadecimal\n";
                return -1;
            }
        }
        r = r + tmp * (unsigned) pow(16, taille - i - 1);
    }
    return r;
}

std::string fonctionsMaths::getByteLine(std::ifstream* f)
{
    if (*f) {
        unsigned int i = 0;
        std::string line;
        char byteLine[33];
        std::getline(*f,line);
        while ((i < 16) && ((i * 3 + 1) < line.length()) ) {
            if (((line[i * 3] < 'a' || line[i * 3]>'f') && (line[i * 3] < 'A' || line[i * 3]>'F') && (line[i * 3] < '0' || line[i * 3]>'9')) 
                || ((line[i * 3 + 1] < 'a' || line[i * 3 + 1]>'f') && (line[i * 3 + 1] < 'A' || line[i * 3 + 1]>'F') && (line[i * 3 + 1] < '0' || line[i * 3 + 1]>'9'))
                ) { //Le caractere scann'e n'est pas un caractere hexadecimal
                byteLine[i * 2] = '\0';
                return byteLine;
            }
            byteLine[i*2] = line[i*3];
            byteLine[(i*2)+1] = line[i * 3 + 1];
            i = i + 1;
        }
        byteLine[i * 2] = '\0';
        return byteLine;
    }
    else
        std::cout << "Erreur ouverture fichier\n";
    return "-1" ;
}



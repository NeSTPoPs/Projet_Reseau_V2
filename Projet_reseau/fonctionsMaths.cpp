#include "fonctionsMaths.h"
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

unsigned long fonctionsMaths::hexToDec(std::string n,int taille)
{
    unsigned long r = 0;
    unsigned long tmp = 0;
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
        r = r + tmp * (unsigned long) pow(16, taille - i - 1);
    }
    return r;
}

std::string fonctionsMaths::getByteLine(std::ifstream* f)
{
    //Analyse UNE SEULE LIGNE du fichier
    if (*f) {
        int i = 0;
        std::string line;
        char byteLine[33];
        std::getline(*f,line);
        while ((i < 16) && (( i * 3 + 1) < line.length()) ) {
            if (((line[ i * 3] < 'a' || line[ i * 3 ]>'f') && (line[i * 3] < 'A' || line[i * 3]>'F') && (line[i * 3] < '0' || line[i * 3]>'9')) 
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

char* fonctionsMaths::getProtocolName(int protocol, char *p)
{
    std::string pName;
    switch (protocol) {
    case 1 :
        pName = "Internet Control Message Protocol (ICMP)";
        break;
    case 2:
        pName = "Internet Group Management Protocol (IGMP)";
        break;
    case 6:
        pName = "Transmission Control Protocol (TCP)";
        break;
    case 8:
        pName = "Exterior Gateway Protocol (EGP)";
        break;
    case 9:
        pName = "any private Interior Gateway Protocol (IGP)";
        break;
    case 17:
        pName = "User Datagram Protocol (UDP)";
        break;
    case 36:
        pName = "XTP";
        break;
    case 46:
        pName = "Reservation Protocol (RSVP)";
        break;
    case 0x800:
        pName = "DoD Internet (Datagramme IP)";
        break;
    case 0x805:
        pName = "X.25 niveau 3";
        break;
    case 0x806:
        pName = "ARP";
        break;
    case 0x8035:
        pName = "RARP";
        break;
    case 0x8098:
        pName = "AppleTalk";
        break;
    default:
        pName = "Protocol non reconnu";
    }
    for (int i = 0; i < pName.length(); i++) {
        p[i] = pName[i];
    }
    p[pName.length()] = '\0';
    return p;
}



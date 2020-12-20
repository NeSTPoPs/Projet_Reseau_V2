#include "fonctionsMaths.h"
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

int fonctionsMaths::est_hexadecimal(char c)
{
    if ((c <= 'f' && c >= 'a') || (c <= 'F' && c >= 'A') || (c <= '9' && c >= '0'))
        return 1;
    return 0;
}

unsigned long fonctionsMaths::hexToDec(std::string n,int taille)
{
    unsigned long r = 0;
    unsigned long tmp = 0;
    for (int i = taille - 1; i >= 0; i = i-1 ){
        if (fonctionsMaths::est_hexadecimal(n[i])) {
            if ((n[i] <= 'f' && n[i] >= 'a') || (n[i] <= 'F' && n[i] >= 'A')) {
                if (n[i] <= 'f' && n[i] >= 'a')
                    tmp = n[i] - 87;
                else
                    tmp = n[i] - 55;
            }
            else {
                if (n[i] <= '9' && n[i] >= '0')
                    tmp = n[i] - 48;
            }
            r = r + tmp * (unsigned long)pow(16, taille - i - 1);
        }
        else {
            // Le caractère n'est pas hexadecimal
            return -1;
        }
    }
    return r;
}



std::string fonctionsMaths::getByteLine(std::string line, int*offset)
{
    //Analyse UNE SEULE LIGNE du fichier
    if (not(line =="")) {
        int i = 0;
        int new_trame = 0;
        static char byteLine[33];
        if (line.length() < 6) {
            // La ligne est trop courte pour etre correct
            return "";
        }
        if (not ((int)fonctionsMaths::hexToDec(line, 4) == *(offset))) { // on vérifie si l'offset correspond à ce qu'on lit  
            if ((int)fonctionsMaths::hexToDec(line, 4) == 0) {// On a une nouvelle trame, on reinitialise l'offset et on met new_trame sur 1
                *offset = 0;
                new_trame = 1;
            }
            else
                return "";  // s'il ne correspond pas et qu'il ne vaut pas 0, on passe directement à la ligne suivante
        }
        line = &(line[5]); // si ça correspond, on passe au contenu de la ligne
        while ((i < 16) && (((unsigned) ( i * 3 + 1)) < ((unsigned) line.length())) ) {
            if ( not(fonctionsMaths::est_hexadecimal(line[i*3])) || not(fonctionsMaths::est_hexadecimal(line[i*3 + 1]) ))
                { //Le caractere scann'e n'est pas un caractere hexadecimal
                byteLine[i * 2] = '\0';
                if (new_trame == 1) {//Il s'agissait d'une nouvelle trame, donc on ajoute un espace pour l'indiquer
                    for (int j = i * 2; j >= 0; j--) { // On decale tous les caracteres d'un cran vers la droite pour ajouter un espace en debut de chaine
                        byteLine[j + 1] = byteLine[j];
                    }
                    byteLine[0] = ' ';
                }
                return byteLine;
            }
            byteLine[i*2] = line[i*3];
            byteLine[(i*2)+1] = line[i * 3 + 1];
            i = i + 1;
            (*offset) = (*offset) + 1;
        }
        byteLine[i * 2] = '\0';
        if (new_trame == 1) {//Il s'agissait d'une nouvelle trame, donc on ajoute un espace pour l'indiquer
            for (int j = i * 2; j >= 0; j--) { // On decale tous les caracteres d'un cran vers la droite pour ajouter un espace en debut de chaine
                byteLine[j + 1] = byteLine[j];
            }
            byteLine[0] = ' ';
        }
        return byteLine;
    }
    return "" ;
}

std::string fonctionsMaths::getByteFile(std::ifstream* f, std::string *chaine)
{
    std::string line;
    std::string byteLine;
    int offset = 0; // initialise offset décimal à 0

    if (f == NULL) {
        std::cout << "Erreur ouverture du fichier\n";
        return "";
    }
    while (getline(*f, line)) {
        byteLine = fonctionsMaths::getByteLine(line, &(offset));
        (*chaine).append(byteLine);
    }
    return (*chaine);
}

char* fonctionsMaths::getIcmpType(int type, char* p) {
    std::string pName;
    switch (type) {
    case 0:
        pName = "Echo Reply";
        break;
    case 3:
        pName = "Destination Unreachable";
        break;
    case 4:
        pName = "Source Quench";
        break;
    case 5:
        pName = "Redirect";
        break;
    case 8:
        pName = "Echo Ping Request";
        break;
    case 11:
        pName = "Time Exceeded";
        break;
    case 12:
        pName = "Parameter Problem";
        break;
    case 13:
        pName = "Timestamp";
        break;
    case 14:
        pName = "Timestamp Reply";
        break;
    case 15:
        pName = "Information Request";
        break;
    case 16:
        pName = "Information Reply";
        break;
    case 17:
        pName = "Address Mask Request";
        break;
    case 18:
        pName = "Address Mask Reply";
        break;
    default:
        pName = "Type non reconnu";
    }
    for (unsigned int i = 0; i <  pName.length(); i++) {
        p[i] = pName[i];
    }
    p[pName.length()] = '\0';
    return p;
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
    for (unsigned int i = 0; i < pName.length(); i++) {
        p[i] = pName[i];
    }
    p[pName.length()] = '\0';
    return p;
}

void fonctionsMaths::afficheMacAdress(int mac[6])
{
    printf("%.2x", mac[0]);
    for (int i = 1; i < 6; i++) {
        printf(".%.2x", mac[i]);
    }
}

void fonctionsMaths::afficheIpAdress(int ip[4])
{
    printf("%i", ip[0]);
    for (int i = 1; i < 4; i++) {
        printf(".%i", ip[i]);
    }
}

unsigned int fonctionsMaths::length(char* chaine)
{
    if (chaine == NULL)
        return 0;
    int i = 0;
    while (chaine[i] != '\0' && chaine[i] != EOF) {
        i++;
    }
    return i;
}




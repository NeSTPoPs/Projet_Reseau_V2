#ifndef DEF_TRAMELIST
#define DEF_TRAMELIST

#include "Trame.h"
#include <iomanip>
#include <iostream>

class TrameList
{
public:
	TrameList();
	TrameList(std::string t); //Argument = texte en hexadecimal, il peut y avoir plusieurs trames
	TrameList(Trame *t);
	~TrameList();

	void ajoute_tete(Trame* t);
	void ajouter_fin(Trame* t);
	void afficherListe();
	void ecrireListe(std::string const fileName);

	Trame* get(int i);
private:
	Trame* element;
	TrameList* suivant;
	TrameList* queue;
};

#endif


#include "TrameList.h"

TrameList::TrameList()
{
	this->element = NULL;
	this->suivant = NULL;
	this->queue = NULL;
}

TrameList::TrameList(std::string t)
{
	this->element = NULL;
	this->suivant = NULL;
	this->queue = NULL;
	char* cstr = new char[t.length() + 1]; //On copie t dans un char * pour faire appel a strtok
	strcpy(cstr, t.c_str());


	char* p = strtok(cstr, " "); // On a un char * correspondant a UNE SEULE trame !
	while (p != NULL)
	{
		Trame *eth = new Trame();
		(*eth).construireTrame(p);
		p = strtok(NULL, " "); 
		this->ajouter_fin(eth);
		
	}
	
	delete[] cstr;
}

TrameList::TrameList(Trame *t)
{
	this->element = t;
	this->suivant = NULL;
	this->queue = NULL;
}

TrameList::~TrameList()
{
	TrameList* tmp = this;
	TrameList* tmp2 = NULL;
	while (tmp) {
		tmp2 = tmp->suivant;
		if (tmp->element) {
			delete (tmp->element);
		}
		tmp = tmp2;
	}
}

void TrameList::ajoute_tete(Trame* t)
{
	TrameList *new_cell = new TrameList(t);
	new_cell->suivant = this;
	*(this) = (*new_cell);
}

void TrameList::ajouter_fin(Trame* t)
{
	if (this->element == NULL) {
		this->element = t;
		return;
	}
	TrameList* new_cell = new TrameList(t);
	if (this->queue == NULL) {
		this->suivant = new_cell;
		this->queue = new_cell;
		return;
	}
	(this->queue)->suivant = new_cell;
	this->queue = new_cell;
}

void TrameList::afficherListe() {
	TrameList* tmp = this;
	int i = 1;
	while (tmp) {
		
		if (tmp->element) {
			printf("\n\n===============TRAME NUMERO %i===============\n\n", i);
			tmp->element->afficherTrame();
		}
		tmp = tmp->suivant;
		i++;
	}
}
Trame* TrameList::get(int i)
{
	TrameList* tmp = this;
	while (tmp && i > 0) {
		tmp = tmp->suivant;
		i--;
	}
	if (tmp == NULL)
		return nullptr;
	return tmp->element;
}

void TrameList::ecrireListe(std::string const fileName) {
	std::ofstream file(fileName);

	if (file)
	{
		TrameList* tmp = this;
		int i = 1;
		while (tmp) {

			if (tmp->element) {
				file << "\n\n===============TRAME NUMERO "<< std::to_string(i) <<"===============\n\n";
				file << tmp->element->toString();
			}
			tmp = tmp->suivant;
			i++;
		}
	}
	else
	{
		std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
	}
	return;
}

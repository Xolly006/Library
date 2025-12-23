#include <stdbool.h>
#ifndef BIBLIOTHEQUE
#define BIBLIOTHEQUE
typedef struct{
	int id;//identifiant unique
	char titre[100];//titre du livre
	char auteur[100];
	int annee;//année de publication du livre
    bool availaible; //disponibilité
}Livre;

typedef struct {
	Livre *Library;//librairie comprenant les livres 
	int max_books ;//nombre maximam de livres qu'elle peut contenir 
	int nb_books; //nombre de livres présents 
} booksLibrary;



#endif

#include <stdbool.h>
#ifndef BIBLIOTHEQUE
#define BIBLIOTHEQUE
typedef struct{
	int id;//identifiant unique
	char titre[100];//titre du livre
	char auteur[100];
	int annee;//année de publication du livre
	//bool emprunt;
}Livre;
#endif

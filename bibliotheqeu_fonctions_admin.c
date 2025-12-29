#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bibliotheque.h"
#include <string.h>
#include <unistd.h>
//ajouter un livre à la bibliotheque 
void addBookToLibrary(booksLibrary*Bibliotheque){
	if(Bibliotheque->nb_books+1<=Bibliotheque->max_books){
		Livre book=saisir_livre();
		//ajouter le livre dans la bibliotheque
		Bibliotheque->Library[Bibliotheque->nb_books]=book;
		printf("Felicitation le livre %s a été ajouté à la bibliothque\n",Bibliotheque->Library[Bibliotheque->nb_books].titre);
		Bibliotheque->Library[Bibliotheque->nb_books].id=Bibliotheque->next_id++;
		Bibliotheque->Library[Bibliotheque->nb_books].available=true;
		Bibliotheque->nb_books+=1;
		//le nombre de livre a ainsi augmenté 
		sauvegarderFichier(Bibliotheque);

	}
    else{
		printf("capacité maximale atteinte impossible d'ajouter un nouveau livre.\n");	
	}
}

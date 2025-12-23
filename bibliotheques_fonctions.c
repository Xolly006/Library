#include <stdio.h>
#include <stdlib.h>
#include "bibliotheque.h"
#include <string.h>
//menu prncipal de la bibliothéque.
void  afficher_menu(){
	int options;
	printf("Bienvenu veuillez choisir l'option qui vous plait : 1-Ajouter un livre \n 2-Afficher un livre \n 3-Rechercher un livre \n 4-Quitter");
	scanf("%d",&options);
		switch (options){
			case 1:
			printf(":::chargement...:::");
			break ;
			case 2:
			printf("très bien ,quel livre voulez-vous afficher");
			break ;
			case 3:
			printf("okay!recherchons ce livre");
			break;
			case 4: 
			printf("à la prochaine");
			break;
			default:
			printf("veuillez choisir une option reelle") ;
		}
}
//fonction pour créer un livre à ajouter à la bibliohèque 
Livre  saisir_livre(){
	Livre book;
	printf("veuillez renseignez les caracteristiques du livre");
	printf("identifiant du livre");
	scanf("%d",&(book).id);
	printf("titre du livre");
	scanf("%s",(book).titre);
	printf("nom de l'auteur");
	scanf("%s",(book).auteur);
	printf("année de parution");
	scanf("%d",&(book).annee);
	return book;
}
void addBookToLibrary(booksLibrary*Bibliotheque){
	if(Bibliotheque->nb_books+1<=Bibliotheque->max_books){
		Livre book=saisir_livre();
		for (int i=0;i<Bibliotheque->nb_books;i++){
			if(book.id==Bibliotheque->Library[i].id){
				printf("ce livre existe déjà!,id déjà existant"); //eviter la duplication d'id;
				return;
			}
		}
		
		Bibliotheque->Library[Bibliotheque->nb_books]=book;
		Bibliotheque->nb_books+=1;
	}
    else{
		printf("capacité maximale atteinte impossible d'ajouter un nouveau livre.");	
	}
}
	

				
		
	

#include <stdio.h>
#include <stdlib.h>
#include "bibliotheque.h"
#include <string.h>
void afficher_menu(){
	printf("Bienvenu veuillez choisir l'option qui vous plait : 1-Ajouter un livre \n 2-Afficher un livre \n 3-Rechercher un livre \n 4-Quitter");
	while (true){
		switch (int options){
			case 1:
			printf(":::chargement...:::");
			break 
			case 2:
			printf("très bien ,quel livre voulez-vous afficher");
			break 
			case 3:
			printf("okay!recherchons ce livre");
			break 
			case 4: 
			printf("à la prochaine");
			break;
			default:
			printf("veuillez choisir une option reelle") ;
		}
}
}
void saisir_livre(Livre *book){
	printf("veuillez renseignez les caracteristiques du livre");
	printf("identifiant du livre");
	scanf("%d",&(*book).id);
	printf("titre du livre");
	scanf("%c",&(*book).titre);
	printf("nom de l'auteur");
	scanf("%c",&(*book).auteur);
	printf("année de parution");
	scanf("%d",&(*book).annee);
	*book={(*book).id;(*book).titre;(*book).auteur;*(book).annee};
}
	
	
				
		
	

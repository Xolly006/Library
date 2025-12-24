#include <stdio.h>
#include <stdlib.h>
#include "bibliotheque.h"
#include <string.h>
//menu principal de la bibliothéque.
void  afficher_menu(booksLibrary *Bibliotheque){
	int options;
	printf("Bienvenu veuillez choisir l'option qui vous plait : 1-Ajouter un livre à la bibliotheque \n 2-Afficher un livre \n 3-Rechercher un livre \n 4-Emprunté un livre  4-Quitter");
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
//ajouter un livre à la bibliotheque 
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
		Bibliotheque->Library[Bibliotheque->nb_books].available=true;
	}
    else{
		printf("capacité maximale atteinte impossible d'ajouter un nouveau livre.\n");	
	}
}
	
//rechercher un livre 
//ma fonction ne doit rien retourner donc void mais elle doit afficher le livre que je cherche à avoir ainsi :
void afficher_livre(Livre book) {
    printf("ID : %d\n", book.id);
    printf("Titre : %s\n", book.titre);
    printf("Auteur : %s\n", book.auteur);
    printf("Année : %d\n", book.annee);

    if (book.available) {
        printf("Statut : disponible\n");
    } else {
        printf("Statut : emprunté\n");
    }

    printf("------------------------\n");
}
//fonction de recherche par titre 
void researchByTitle(booksLibrary *Bibliotheque,char*titre){
	int trouve=0;
	for (int i=0;i<Bibliotheque->nb_books;i++){
		if (strcmp(Bibliotheque->Library[i].titre,titre)==0){
			afficher_livre(Bibliotheque->Library[i]);
			trouve++;
		}
	}
	if (!trouve){
		printf("Aucun livre trouvé ! \n");
	}
}
// rechercher par auteur 
void resarchByAutor(booksLibrary *Bibliotheque,char*Autor){
	int trouve=0;
	for (int i=0;i<Bibliotheque->nb_books;i++){
		if(strcmp(Bibliotheque->Library[i].auteur,Autor)==0){
			afficher_livre(Bibliotheque->Library[i]);
			trouve++;
		}
	}
	if(!trouve){
		printf("Aucun livre ne correspond à cet auteur !\n");
	}
}
// rechercher par id ?
void researchbyId(booksLibrary *Bibliotheque ,int id ){
	int trouve=0;
	for(int i=0;i<Bibliotheque->nb_books;i++){
		if (Bibliotheque->Library[i].id==id){
			afficher_livre(Bibliotheque->Library[i]);
			trouve++;
		}
	}
	if (!trouve){
     	printf("aucun id correspondant vous pouvez toujours reessayer\n");
	}
}
Livre research(booksLibrary *Bibliotheque){
	int research_value;
	printf(":::::Rechercher par genre:::::");
	printf("vous pouvez rechercher suivant :1- le titre, 2-les noms des auteurs ,3-l'année de parution  nous intégrerons bientôt un système qui donnera le resultat le plus optimal");
	printf("rechercher");
	scanf("%d",&research_value);
	switch(research_value){
		case 1:{
			printf("très bien vous rechercher par le titre ");
			char title[50];
			printf("Entrez le titre: ");
			fgets (title,sizeof(title),stdin);
			title[strcspn(title,"\n")]='\0';
			researchByTitle(Bibliotheque,title);
			break;
		}
		case 2:{
			printf("très bien vous rechercher par l'auteur plutôt cultivé je l'admet ");
			char Autor[50];
			printf("Entrez le nom de l'auteur : ");
			fgets(Autor,sizeof(Autor),stdin);
			Autor[strcspn(Autor,"\n")]='\0';
			resarchByAutor(Bibliotheque,Autor);
			break;
	    }
		case 3:{ //seulement et sûrement pour les admin 
			printf("une recherche par id ? interessant ");
			int id;
			printf("Entrez l'identifiant unique du livre :");
			scanf("%d",&id);
			researchbyId(Bibliotheque,id);
			break;
		}
		default:
		printf("De nouvaux paramètres seront ajoutés plus tard merci de vous contenter de ceux disponibles pour le moment \n");
		break;
		
	}
}
//fonction d'emprunt de livre 
void book_emprunt(Livre* book){
	if (!book->available){
		printf("Le livre est déjà emprunté\n");
	}
	book->available = false;
	printf("vous avez emprunté '%s'\n",book->titre);
}
//fonction de remise de livre evidemment!
void book_remise(Livre *book){
	book->available=true;
}



				
		
	

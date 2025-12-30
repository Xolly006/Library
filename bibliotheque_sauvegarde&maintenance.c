#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bibliotheque.h"
#include <string.h>
#include <unistd.h>
//vider le buffer après chaque scanf 
void vider_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
} 
//sauvegarder en temps reel les caractéristiques des livres dans un fichier un peu comme un data base :
void sauvegarderFichier(booksLibrary*Bibliotheque){
	FILE*fichier=fopen(Bibliotheque->myFile,"w");
	if(fichier==NULL){
		printf("Erreur de lecture de %s",Bibliotheque->myFile);
		return;
	}
	//sauvegarder la taille maximale
	fprintf(fichier,"%d\n",Bibliotheque->max_books);
	//sauvegarder les livres 
	for(int i=0;i<Bibliotheque->nb_books;i++){
		fprintf(
			fichier ,"%d|%s|%s|%d|%d\n",
			Bibliotheque->Library[i].id,
			Bibliotheque->Library[i].titre,
			Bibliotheque->Library[i].auteur,
			Bibliotheque->Library[i].annee,
			Bibliotheque->Library[i].available
		);
	}
    fclose(fichier);
	printf(">>Bibliothèque sauvegardée avec succès\n");
}
//charger le fichier sauvegardé
int chargerFichier(booksLibrary*Bibliotheque){
	FILE *fichier=fopen(Bibliotheque->myFile,"r");
	if(fichier==NULL){
		printf("Aucun fichier du nom %s existant création d'un nouveau fichier\n",Bibliotheque->myFile);
		return 0;
	}
	if(fscanf(fichier,"%d\n",&Bibliotheque->max_books)!=1){
		printf("Erreur:fichier corrompu ou vide");
		fclose(fichier);
		return 0;
	}
	Bibliotheque->Library=malloc(Bibliotheque->max_books*sizeof(Livre));
	if(!Bibliotheque->Library){
		printf("erreur d'allocation mémoire");
		fclose(fichier);
		return 0;
	}
	Bibliotheque->nb_books = 0;
	Bibliotheque->next_id=1;
	Livre b;
	int temp;
	//scanf extreme pour lire jusqu'au delimiteurs
	while(fscanf(fichier,"%d|%[^|]|%[^|]|%d|%d\n",&b.id,b.titre,b.auteur,&b.annee,&temp)==5){
		b.available=temp?true:false;
		if(Bibliotheque->nb_books<Bibliotheque->max_books){
			Bibliotheque->Library[Bibliotheque->nb_books]=b;
            Bibliotheque->nb_books++;
			// Mettre à jour next_id pour qu'il soit toujours supérieur au plus grand ID
			if (b.id >= Bibliotheque->next_id){
				Bibliotheque->next_id = b.id + 1;
			}
		}
	}
	fclose(fichier);
	printf("%d livres chargés depuis le fichier.\n", Bibliotheque->nb_books);
	return 1;
}
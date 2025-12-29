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
	printf("Bibliothèque sauvegardée avec succès\n");
}
//charger le fichier sauvegardé
void chargerFichier(booksLibrary*Bibliotheque){
	FILE *fichier=fopen(Bibliotheque->myFile,"r");
	if(fichier==NULL){
		printf("Aucun fichier du nom %s existant création d'un nouveau fichier\n",Bibliotheque->myFile);
		Bibliotheque->nb_books = 0;
	    Bibliotheque->next_id=1;
		return;
	}
	Bibliotheque->nb_books = 0;
	Bibliotheque->next_id=1;
	Livre b;
	int temp;
	while(fscanf(fichier,"%d|%[^|]|%[^|]|%d|%d\n",&b.id,b.titre,b.auteur,&b.annee,&temp)==5){
		b.available=temp?true:false;
		if(Bibliotheque->nb_books<Bibliotheque->max_books){
			Bibliotheque->Library[Bibliotheque->nb_books]=b;
            Bibliotheque->nb_books++;
			if (b.id >= Bibliotheque->next_id){
				Bibliotheque->next_id = b.id + 1;
			} //calcul le plus grand id existant next_id doit être supp au plus grand id qui existe
		}
	}
	fclose(fichier);
	printf("%d livres chargés depuis le fichier.\n", Bibliotheque->nb_books);
}
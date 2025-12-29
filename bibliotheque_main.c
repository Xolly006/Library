#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bibliotheque.h"
int main() {
    booksLibrary Bibliotheque;
    printf("Nombre maximal e livre dans la bibliothèque :");
	scanf("%d",&Bibliotheque.max_books);
	vider_buffer();
    Bibliotheque.Library = malloc(Bibliotheque.max_books * sizeof(Livre));
	if (Bibliotheque.Library == NULL) {
    printf("Erreur d'allocation mémoire\n");
    return 1;
 } 

    printf("Nom de la bibliothèque à charger ou créer : ");
    fgets(Bibliotheque.myFile, sizeof(Bibliotheque.myFile), stdin);
    Bibliotheque.myFile[strcspn(Bibliotheque.myFile, "\n")] = '\0';
    chargerFichier(&Bibliotheque);
    afficher_menu(&Bibliotheque);
    free(Bibliotheque.Library);
    return 0;
}

	

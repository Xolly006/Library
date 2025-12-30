#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotheque.h"

int main() {
    booksLibrary Bibliotheque;
    // Initialisation par défaut
    Bibliotheque.Library = NULL;
    Bibliotheque.nb_books = 0;
    Bibliotheque.next_id = 1;

    int primeChoice;

    printf("Bienvenu(e) !\n");
    printf("1 - Creer une nouvelle bibliotheque\n");
    printf("2 - Charger une bibliotheque existante\n");
    printf("Votre choix : ");
    scanf("%d", &primeChoice);
    vider_buffer();

    printf("Entrez le nom du fichier (ex: ma_biblio.txt) : ");
    fgets(Bibliotheque.myFile, sizeof(Bibliotheque.myFile), stdin);
    Bibliotheque.myFile[strcspn(Bibliotheque.myFile, "\n")] = '\0';

    if (primeChoice == 1) {
        // --- CRÉATION ---
        printf("Quelle est la capacite maximale de la bibliotheque ? ");
        scanf("%d", &Bibliotheque.max_books);
        vider_buffer();

        Bibliotheque.Library = malloc(Bibliotheque.max_books * sizeof(Livre));
        if (!Bibliotheque.Library) {
            printf("Erreur mémoire !\n");
            return 1;
        }
        
        // On sauvegarde immédiatement pour créer le fichier vide avec l'en-tête
        sauvegarderFichier(&Bibliotheque);
        
    } else if (primeChoice == 2) {
        // --- CHARGEMENT ---
        if (!chargerFichier(&Bibliotheque)) {
            printf("Le fichier '%s' n'existe pas.\n", Bibliotheque.myFile);
            printf("Voulez-vous le creer ? (oui/non) : ");
            char choix[10];
            fgets(choix, sizeof(choix), stdin);
            choix[strcspn(choix, "\n")] = '\0';

            if (strcmp(choix, "oui") == 0) {
                printf("Taille de votre nouvelle bibliotheque : ");
                scanf("%d", &Bibliotheque.max_books);
                vider_buffer();
                
                Bibliotheque.Library = malloc(Bibliotheque.max_books * sizeof(Livre));
                sauvegarderFichier(&Bibliotheque);
            } else {
                printf("Au revoir !\n");
                return 0;
            }
        }
    } else {
        printf("Choix invalide.\n");
        return 1;
    }

    // Ici, Bibliotheque est correctement initialisée et chargée
    afficher_menu(&Bibliotheque); 
    // libéreration de  la mémoire à la fin
    if (Bibliotheque.Library) {
        free(Bibliotheque.Library);
    }
    
    return 0;
}
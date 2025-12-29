#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bibliotheque.h"
#include <string.h>
#include <unistd.h>


void Simulation_temps(){
	for(int i=0;i<3;i++){
		printf(".");
		fflush(stdout);
		usleep(500000);
	}
	printf("Terminé!");
}

//fonction pour créer un livre à ajouter à la bibliohèque 
Livre  saisir_livre(){
	Livre book;
	printf("=======------------NOUVEAU LIVRE------------=======\n");
	printf("veuillez renseignez les caracteristiques du livre\n");
	printf("titre du livre : ");
	fgets(book.titre,sizeof(book.titre),stdin);
	book.titre[strcspn(book.titre,"\n")]='\0';
	printf("nom de l'auteur : ");
	fgets(book.auteur,sizeof(book.auteur),stdin);
	book.auteur[strcspn(book.auteur,"\n")]='\0';
	printf("année de parution : ");
	scanf("%d",&(book).annee);
	vider_buffer();
	return book;
}

//fonction pour afficher la bibliotheque et les livres dispo 
void afficherLivresDisponibles(booksLibrary *Bibliotheque) {
	printf("--- Liste des livres disponibles ---\n");

    for (int i = 0; i < Bibliotheque->nb_books; i++) {
        // Si le livre est emprunté, on passe au suivant sans rien afficher
        if (Bibliotheque->Library[i].available == false) {
            continue; // On remonte au i++ immédiatement grace à continue
        }

        // Ce code ne sera exécuté QUE si available est true
        printf("ID: %d | Titre: %s\n", Bibliotheque->Library[i].id, Bibliotheque->Library[i].titre);
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
int researchByTitle(booksLibrary *Bibliotheque,char*titre,int *id_trouve){
	int trouve=0;
	int ids=0;
	for (int i=0;i<Bibliotheque->nb_books;i++){
		if (strstr(Bibliotheque->Library[i].titre, titre) != NULL){
			id_trouve[trouve]=Bibliotheque->Library[i].id; 
			trouve++;
		}//strstr plus polyvalent pour les recherches
	}
	return trouve;
}

// rechercher par auteur 
int resarchByAutor(booksLibrary *Bibliotheque,char*Autor,int* id_trouve){
	int trouve=0;
	for (int i=0;i<Bibliotheque->nb_books;i++){
		if(strstr(Bibliotheque->Library[i].auteur, Autor) != NULL){
			id_trouve[trouve]=Bibliotheque->Library[i].id;
			trouve++;
		}
	}
	return trouve;
}

// rechercher par id ?
int researchbyId(booksLibrary *Bibliotheque ,int id,int* id_trouve ){
	int trouve=0;
	for(int i=0;i<Bibliotheque->nb_books;i++){
		if (Bibliotheque->Library[i].id==id){
			id_trouve[0]=Bibliotheque->Library[i].id;
		}
		return 1;//un livre trouvé unicité de l'id
	}
	return 0;
}

//fonction pour lier l'index aux identifiants dans la bibliotheque 
int researchIndexByid(booksLibrary *Bibliotheque ,int id ){
	for(int i=0;i<Bibliotheque->nb_books;i++){
		if(Bibliotheque->Library[i].id==id){
			return i;
		}
	}
	return -1;
}

void afficherLivrestrouves(booksLibrary*Bibliotheque,int trouve,int*id_trouve){
	printf("\n=== Résultats trouvés : %d livre(s) ===\n", trouve);
	for(int i=0;i<trouve;i++){
		int index=researchIndexByid(Bibliotheque,id_trouve[i]);
		 if (index != -1) {
            printf("\n[%d] ID: %d | %s | %s | %d\n", 
                   i + 1,  // Numéro de 1 à N
                   Bibliotheque->Library[index].id,
                   Bibliotheque->Library[index].titre,
                   Bibliotheque->Library[index].auteur,
                   Bibliotheque->Library[index].annee);
            
            if (!Bibliotheque->Library[index].available) {
                printf("    ⚠️  Déjà emprunté\n");
            }
        }
    }
    printf("\n");

}

int research(booksLibrary *Bibliotheque,int *id_trouve){
	int research_value;
	int trouve=0;
	printf("\n::::: Rechercher par genre :::::\n");
    printf("1 - Par titre\n");
    printf("2 - Par auteur\n");
    printf("3 - Par ID\n");
    printf("Votre choix : ");
    scanf("%d", &research_value);
    vider_buffer();
	switch(research_value){
		case 1:{
			Simulation_temps();
			printf("\n");
			printf("très bien vous rechercher par le titre ");
			char title[50];
			printf("Entrez le titre: ");
			fgets (title,sizeof(title),stdin);
			title[strcspn(title,"\n")]='\0';
			trouve=researchByTitle(Bibliotheque,title,id_trouve);
			break;
		}
		case 2:{
			Simulation_temps();
			printf("\n");
			printf("très bien vous rechercher par l'auteur plutôt cultivé je l'admet ");
			char Autor[50];
			printf("Entrez le nom de l'auteur : ");
			fgets(Autor,sizeof(Autor),stdin);
			Autor[strcspn(Autor,"\n")]='\0';
			trouve=resarchByAutor(Bibliotheque,Autor,id_trouve);
			break;
	    }
		case 3:{ 
			Simulation_temps();
			printf("\n");
			printf("une recherche par id ? interessant ");
			int id;
			printf("Entrez l'identifiant unique du livre :");
			scanf("%d",&id);
			vider_buffer();
			trouve=researchbyId(Bibliotheque,id,id_trouve);
			break;
		}
		default:{
			printf("Faites un choix valide!\n");
		    break;
		}
	}

	if(trouve==0){
		printf("Aucun resultat trouvé");
	}
	else{
		afficherLivrestrouves(Bibliotheque,trouve,id_trouve);
	}
	
	return trouve;
}
//fonction d'emprunt de livre 
void book_emprunt(Livre* book,booksLibrary*Bibliotheque){
	if (!book->available){
		printf("Le livre est déjà emprunté\n");
		return ;
	}
	book->available = false;
	printf("vous avez emprunté '%s'\n",book->titre);
	sauvegarderFichier(Bibliotheque);
}
//fonction de remise de livre evidemment!
void book_remise(Livre *book,booksLibrary *Bibliotheque){
	book->available=true;
	printf("Merci le livre a été rendu\n ");
	sauvegarderFichier(Bibliotheque);
}

//menu principal
//menu principal de la bibliothéque.
void  afficher_menu(booksLibrary *Bibliotheque){
	int options=0;
	while(options != 5) {
		       printf("\n╔════════════════════════════════════════╗\n");
        printf("║         MENU BIBLIOTHÈQUE             ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("\n--- MENU ---\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher les livres\n");
        printf("3. Rechercher / Emprunter\n");
        printf("4. Rendre un livre\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &options);
        vider_buffer();
	
			switch (options){
				case 1:{
					printf(":::chargement:::\n");
					addBookToLibrary(Bibliotheque);
					break ;
				}
				case 2:{
					printf("très bien ,voici la bibliothèque!\n");
					afficherLivresDisponibles(Bibliotheque);
					break ;
				}
				case 3:{
					int id_trouve[100];
					int trouve=research(Bibliotheque,id_trouve);
					if(trouve==0){
						break;
					}
					char choix[50];
					printf("voulez vous emprunter un livre ? : ");
					fgets(choix,sizeof(choix),stdin);
					choix[strcspn(choix,"\n")]='\0';
					if(strcmp(choix,"oui")!=0){
						printf("Bye");
						break;
					}
					int choix_numero=-1;
					int id_choisi=-1;
					int index=-1;
					if(trouve==1){
						id_choisi=id_trouve[0];
						printf("Selection automatique de l'unique livre");
					}
					//au cas où il y a plusieurs livres
				    else{
						while(choix_numero!=0){
							printf("Quel live voulez-vous emprunter (1-%d) 0 pour annulez: ",trouve);
							scanf("%d",&choix_numero);
							vider_buffer();
							if(choix_numero==0){
								break;
							}
							if(choix_numero<1||choix_numero>trouve){
								printf("Faites un choix valide!\n");
								continue;
							}
							id_choisi=id_trouve[choix_numero-1];
							break;
						}
					}
					if(id_choisi==-1){
						break;
					}
					index=researchIndexByid(Bibliotheque,id_choisi);
					if(index==-1){
						printf("Erreur:Livre non trouvé");
						break;
					}
					printf("\n=== Vous avez sélectionné ===\n");
					afficher_livre(Bibliotheque->Library[index]);
					printf("Emprunter ce livre?\n");
					printf("oui\n");
					printf("non\n");
					printf("votre choix : ");
					fgets(choix,sizeof(choix),stdin);
					choix[strcspn(choix,"\n")]='\0';
					if(strcmp(choix,"oui")!=0){
						printf("okay");
						break;
					}
					book_emprunt(&Bibliotheque->Library[index],Bibliotheque);
					break;
				}
				case 4:{
					printf("Très bien vous souhaitez rendre un livre");
					int id;
					int index=-1;
					do{
						printf("Entrez l'id du livre que vous souhaitez rendre \n(Entrez 0 si vous voulez sortir du code )\n");
						scanf("%d",&id);
						vider_buffer();
						if(id==0){
							break;
						}
						index=researchIndexByid(Bibliotheque,id);
						if(index==-1){
							printf("Entrez un identifiant existant !");
						}
					}while(index==-1);
					if(index!=-1){
						book_remise(&Bibliotheque->Library[index],Bibliotheque);
						printf("Merci et au-revoir");
					}//nous lions l'index et l'identifions ainsi grâce à researchindexbyid la fonction retourne l'index (la position du livre ) grâce à son identifiant 
				break;
				}
				case 5:{
				printf("à la prochaine\n");
				break;
				}
				
				default:
				printf("veuillez choisir une option reelle") ;
			}
	}
}					
			
		

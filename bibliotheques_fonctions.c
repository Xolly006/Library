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
void Simulation_temps(){
	for(int i=0;i<3;i++){
		printf(".");
		fflush(stdout);
		usleep(500000);
	}
	printf("Terminé!");
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
		printf("Aucun fichier du nom %s existant création d'un nouveau fichier\n");
		Bibliotheque->nb_books = 0;
	    Bibliotheque->next_id=1;
		return;
	}
	Bibliotheque->nb_books = 0;
	Bibliotheque->next_id=1;
	Livre b;
	while(fscanf(fichier,"%d|%[^|]|%[^|]|%d|%d\n",&b.id,b.titre,b.auteur,&b.annee,&b.available)==5){
		if(Bibliotheque->nb_books<Bibliotheque->max_books){
			Bibliotheque->Library[Bibliotheque->nb_books]=b;
            Bibliotheque->nb_books++;
			if (b.id >= Bibliotheque->next_id){
				Bibliotheque->next_id = b.id + 1;
			} //calcul le plus grand id existant next_id doit être supp au plus grand id qui existe
		}
	}
	fclose(fichier);
	printf("%d livres charges depuis le fichier.\n", Bibliotheque->nb_books);
}
//fonction pour créer un livre à ajouter à la bibliohèque 
Livre  saisir_livre(){
	Livre book;
	printf("=======------------NOUVEAU LIVRE------------=======\n");
	printf("veuillez renseignez les caracteristiques du livre");
	vider_buffer();
	printf("titre du livre");
	fgets(book.titre,sizeof(book.titre),stdin);
	book.titre[strcspn(book.titre,"\n")]='\0';
	printf("nom de l'auteur");
	fgets(book.auteur,sizeof(book.auteur),stdin);
	book.auteur[strcspn(book.auteur,"\n")]='\0';
	printf("année de parution");
	scanf("%d",&(book).annee);
	vider_buffer();
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
		//ajouter le livre dans la bibliotheque
		Bibliotheque->Library[Bibliotheque->nb_books]=book;
		printf("Felicitation le livre %s a été ajouté à la bibliothque",Bibliotheque->Library[Bibliotheque->nb_books].titre);
		Bibliotheque->Library[Bibliotheque->nb_books].available=true;
		Bibliotheque->nb_books+=1;
		Bibliotheque->Library[Bibliotheque->nb_books].id=Bibliotheque->next_id++;
		//le nombre de livre a ainsi augmenté 
		sauvegarderFichier(Bibliotheque);

	}
    else{
		printf("capacité maximale atteinte impossible d'ajouter un nouveau livre.\n");	
	}
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
void researchByTitle(booksLibrary *Bibliotheque,char*titre){
	int trouve=0;
	for (int i=0;i<Bibliotheque->nb_books;i++){
		if (strstr(Bibliotheque->Library[i].titre, titre) != NULL){
			afficher_livre(Bibliotheque->Library[i]);
			trouve++;
		}//strstr plus polyvalent pour les recherches
	}
	if (!trouve){
		printf("Aucun livre trouvé ! \n");
	}
}
// rechercher par auteur 
void resarchByAutor(booksLibrary *Bibliotheque,char*Autor){
	int trouve=0;
	for (int i=0;i<Bibliotheque->nb_books;i++){
		if(strstr(Bibliotheque->Library[i].auteur, Autor) != NULL){
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
void research(booksLibrary *Bibliotheque){
	int research_value;
	printf(":::::Rechercher par genre:::::");
	printf("vous pouvez rechercher suivant :1- le titre, 2-les noms des auteurs ,//3-l'année de parution  nous intégrerons bientôt un système qui donnera le resultat le plus optimal");
	printf("rechercher");
	scanf("%d",&research_value);
	vider_buffer();
	switch(research_value){
		case 1:{
			Simulation_temps();
			printf("très bien vous rechercher par le titre ");
			char title[50];
			printf("Entrez le titre: ");
			fgets (title,sizeof(title),stdin);
			title[strcspn(title,"\n")]='\0';
			researchByTitle(Bibliotheque,title);
			break;
		}
		case 2:{
			Simulation_temps();
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
			vider_buffer();
			researchbyId(Bibliotheque,id);
			break;
		}
		default:
		printf("De nouvaux paramètres seront ajoutés plus tard merci de vous contenter de ceux disponibles pour le moment \n");
		break;
		
	}
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
//fonction pour lier l'index aux identifiants dans la bibliotheque 
int researchIndexByid(booksLibrary *Bibliotheque ,int id ){
	for(int i=0;i<Bibliotheque->nb_books;i++){
		if(Bibliotheque->Library[i].id==id){
			return i;
		}
	}
	return -1;
}

//menu principal
//menu principal de la bibliothéque.
void  afficher_menu(booksLibrary *Bibliotheque){
	int options=0;
	while(options != 5) {
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
					printf(":::chargement...:::");
					addBookToLibrary(Bibliotheque);
					break ;
				}
				case 2:{
					printf("très bien ,voici la bibliothèque!");
					afficherLivresDisponibles(Bibliotheque);
					break ;
				}
				case 3:{
					printf("okay!recherchons ce livre");
					research(Bibliotheque);
					int choix;
					printf("Souhaitez vous emprunter ce livre ? 1-oui 2-non");
					scanf("%d",&choix);
					vider_buffer();
					if(choix==1){
						printf("vous avez maintenant l'id du livre grâce à votre recherche vous pouvez l'emprunter");
						int id ;
						int index=-1;
						do{
							printf("entrez l'id s'il vous plaît :");
							scanf("%d",&id);
							vider_buffer();
							index=researchIndexByid(Bibliotheque,id);
							if(index==-1){
								printf("reessayer");
							}
						}while(index==-1);
						if(index!=-1){
							book_emprunt(&Bibliotheque->Library[index]);
							printf("N'oublier pas de rendre le livre plus tard \n");
						}
					}
					else{
						printf("Très bien ");
						break ;
					}
					break;
				}
				case 4:{
					printf("Très bien vous souhaitez rendre un livre");
					int id;
					int index=-1;
					do{
						printf("Entrez l'id du livre que vous souhaitez rendre (Entrez 0 si vous voulez sortir du code )");
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
						book_remise(&Bibliotheque->Library[index]);
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
			
		

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BIBLIOTHEQUE
#define BIBLIOTHEQUE
	typedef struct{
		int id;//identifiant unique
		char titre[100];//titre du livre
		char auteur[100];
		int annee;//année de publication du livre
		bool available; //disponibilité
	}Livre;

	typedef struct {
		char myFile[100];
		Livre *Library;//librairie comprenant les livres 
		int max_books ;//nombre maximam de livres qu'elle peut contenir 
		int nb_books; //nombre de livres présents 
		int next_id;
	} booksLibrary;
	//fonctions pour maintenir le code (empêcher le crash)
	void vider_buffer();
	
	//les fonctions de sauvegarde
	void sauvegarderFichier(booksLibrary*Bibliotheque);
	void chargerFichier(booksLibrary*Bibliotheque);

	//les fonctions liées au livre
    Livre  saisir_livre();
	void afficher_livre(Livre book);
    void book_emprunt(Livre* book,booksLibrary*Bibliotheque);
	void book_remise(Livre *book,booksLibrary*Bibliotheque);

	//les fonctions pour la bibliothèque
	void addBookToLibrary(booksLibrary*Bibliotheque);
	void afficherLivresDisponibles(booksLibrary *Bibliotheque) ;
    void researchByTitle(booksLibrary *Bibliotheque,char*titre);
	void resarchByAutor(booksLibrary *Bibliotheque,char*Autor);
	void researchbyId(booksLibrary *Bibliotheque ,int id );//pas evident que tout le monde arrive à s'en servir garder un id c'est plutôt complexe
	//plus tard je créerai un générateur d'id random mais je ne pense pas trop que ce sera utile 
	void research(booksLibrary *Bibliotheque);
    int researchIndexByid(booksLibrary *Bibliotheque ,int id );

    //menu principal
	void  afficher_menu(booksLibrary *Bibliotheque);
	//expérience utilisateur
	void Simulation_temps();


#endif
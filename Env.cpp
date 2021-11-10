#include <iostream>
#include <fstream>
#include <new>
#include "Env.hpp"


Env::Env(int largeur, int hauteur, int longueur)
	:largeur_(largeur), hauteur_(hauteur), longueur_(longueur)
{
	tableau_ = new Case[hauteur*largeur*longueur];

	setPenteCsv("donnée-cours-d'eau.csv");

	// initie le tableau représentant la rivière
	//initTableau(largeur_, hauteur_, longueur_);
}

//mettre main sûrement?
void Env::readCsv(int x, int y, std::string filename, std::vector<double*&> data, int colonne, int ligne) { // Mettre dans main ?

	ifstream myFile;
	myFile.open(filename); // mettre que si pas ouvert erreur
	double cell;

	for(int i = 0; i < x * y; i++) {

		if (myFile.good()) {
			getline(myFile, cell, ',');
		} else {
			break; // si c'est pas good on veut que ça finisse la boucle for
		}

		if (colonne == -1 and ligne == -1) {

			data.push_back(cell);

		} else if (colonne == -1) {

			if (i / x == ligne) { //vérifier
				data.push_back(cell);
			}

		} else if (ligne == -1) {

			if (i % x == colonne) { // le i != colonne pour éviter la première ligne de titre mais un peu trop spécifique à ce fichier ? est ce qu'il compte  dans le fichier csv ?
				data.push_back(cell);
			}

		} else { // plus que l'option ou ligne et colonne != -1

			if (i % x == colonne and i / x == ligne) { // corriger si on change les conditions précédentes
				data.push_back(cell);
			}
		}
	}
}

void Env::setPenteCsv(std:string filename) {
	int x_size = 36;
	int y_size = 23;
	//colonne 9 (8) 36 x 23 (cases tableau)
	for (int i = 1; i < y_size; i++) { // la boucle permet d'appeler readCsv pour toutes les lignes sauf la première (comme ça la fonction readCsv est plus général, pas besoin d'y enlever la première ligne)
	readCsv(x_size, y_size, filename, data_pente_, 8, i);
	}
	double somme = 0;
	for(int i = 0; i< data_pente_.size(); i++){
			somme = somme + data_pente_[i];
	}
	pente_ = somme / (y_size-1);
	cout << "La pente est: "<< pente_ << endl;
}
/*
void Env::initTableau(int largeur, int hauteur, int longueur) {

	//tableau de structure en 3D
	int grandeur = hauteur * longueur * largeur;

	// z vers le haut, y vers la largeur, x vers la longueur
	int i = (z * (largeur) + y) + largeur * hauteur * x;

	//double pente();
	//double h_eau = hauteur_eau(pente, debit);

	int h_sol = 1/100 * hauteur; // initialement
	int x = 0;
	int y = 0;
	int z = 0;

	for(int i = 0; i <= grandeur; i++){

		calcul_pente(h_sol)
		y =+ 1;

		if(i == (largeur-1) + z * largeur + x * largeur + hauteur){ // à chaque largeur finit, on monte dans le tableau
			z =+1;
			y = 0;
		}

		if(z == hauteur + 1){
		//une fois le haut du tableau atteint
			z = 0;
			x =+ 1;
			// on avance selon x et on commence en bas
		}

		if(z <= h_sol){
			model[i].matiere_.sol_.etat = true;
			model[i].matiere_.sol_.x_ = x;
			model[i].matiere_.sol_.y_ = y;
			model[i].matiere_.sol_.z_ = z;
		}

		if(z > h_sol){
			model[i].matiere_.eau_.etat = true;
			model[i].matiere_.eau_.x_ = x;
			model[i].matiere_.eau_.y_ = y;
			model[i].matiere_.eau_.z_ = z;
		}
		if(z > h_eau){
			model[i].matiere_.air_.etat = true;
			model[i].matiere_.air_.x_ = x;
			model[i].matiere_.air_.y_ = y;
			model[i].matiere_.air_.z_ = z;
		}
	}
	tableau_ = &tableau;
}*/

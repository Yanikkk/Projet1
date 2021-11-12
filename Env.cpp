#include <iostream>
#include <fstream>
#include <new>
#include "Env.hpp"



Env::Env(int largeur, int hauteur, int longueur)
	:largeur_(largeur), hauteur_(hauteur), longueur_(longueur)
{
	tableau_ = new Case[hauteur*largeur*longueur];
	
	setPenteCsv("donnee-cours-deau.csv");

	// initie le tableau représentant la rivière
	initTableau(largeur_, hauteur_, longueur_);
}

//mettre main sûrement?
// fonction pour read des csv séparé par des ";" et pouvant prendre des "double"
// penser si on veut faire fonction générale (mettre un char en argument ou autre)
void Env::readCsv(int x, int y, string filename, vector<double*>& data, int colonne, int ligne) { // Mettre dans main ?

	ifstream myFile;
	myFile.open(filename); // mettre que si pas ouvert erreur
	string cell;
	
	
	for(int i = 0; i < x * y; i++) {
		
		if (myFile.good()) {
			getline(myFile, cell, ',');
			
			
		} else {
			break; // si c'est pas good on veut que ça finisse la boucle for
		}
		
		

		if (colonne == -1 and ligne == -1) {
			double* cell_d = new double (stod(cell));
			data.push_back(cell_d);
			

		} else if (colonne == -1) {

			if (i / x == ligne) { //vérifier
				double* cell_d = new double (stod(cell));
				data.push_back(cell_d);
			}

		} else if (ligne == -1) {

			if (i % x == colonne) { // le i != colonne pour éviter la première ligne de titre mais un peu trop spécifique à ce fichier ? est ce qu'il compte  dans le fichier csv ?
				double* cell_d = new double (stod(cell));
				data.push_back(cell_d);
			}

		} else { // plus que l'option ou ligne et colonne != -1

			if (i % x == colonne and i / x == ligne) { // corriger si on change les conditions précédentes
				
				double* cell_d = new double (stod(cell));
				data.push_back(cell_d);
				
			}
		}
	}
}

void Env::setPenteCsv(string filename) {
	int x_size = 36;
	int y_size = 23;
	vector<double*> data_pente; ///< données csv
	//colonne 9 (8) 36 x 23 (cases tableau)
	for (int i = 1; i < y_size; i++) { // la boucle permet d'appeler readCsv pour toutes les lignes sauf la première (comme ça la fonction readCsv est plus général, pas besoin d'y enlever la première ligne)
	readCsv(x_size, y_size, filename, data_pente, 8, i);
	}
	double somme = 0;
	for(unsigned int i = 0; i< data_pente.size(); i++){
			
			somme = somme + *data_pente[i];
			delete data_pente[i];
			data_pente[i] = nullptr;
	}
	data_pente.clear();
	pente_ = somme / (y_size-1);
}

void Env::initTableau(int largeur, int hauteur, int longueur) {

	//tableau de structure en 3D
	int grandeur = hauteur * longueur * largeur;

	int h_sol = 1; // initialement, une couche de terre au minimum
	int x = 0;
	int y = 0;
	int z = 0;
	
	// z vers le haut, y vers la largeur, x vers la longueur
	//int i = (z * (largeur) + y) + largeur * hauteur * x;

	//double h_eau = hauteur_eau(pente, debit);

	

	for(int i = 0; i <= grandeur; i++){
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
			//ici h_sol change
		}

		if(z <= h_sol){
			model[i].matiere_.sol_.etat = true;
			model[i].matiere_.sol_.x_ = x;
			model[i].matiere_.sol_.y_ = y;
			model[i].matiere_.sol_.z_ = z;
		}

		if(h_eau > z and z > h_sol){
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
}

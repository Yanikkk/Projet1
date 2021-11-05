#include <iostream>
#include <fstream>
#include <string>
#include <new>
#include "Env.hpp"


Env::Env(int largeur, int hauteur, int longueur)
	:largeur_(largeur), hauteur_(hauteur), longueur_(longueur)
{
	tableau_ = new case[hauteur*largeur*longueur];
	
	pente_ = setPenteCsv();
	
	// initie le tableau représentant la rivière
	initTableau(largeur_, hauteur_, longueur_); 
}

//mettre main sûrement?
void Env::readCsv(int x, int y, string filename, vector<double*&> data, int colonne = -1, int ligne = -1) { // Mettre dans main ? 
	
	ifstream myFile;
	myFile.open(filename);
	int x_size = x;
	int y_size = y;
	
	for(int i = 0; i < x_size * y_size; i++) {
		double line; 
		if (myFile.good()) {
			
			getline(myFile, line, ',');			
		}
		
		
		if ((i % x_size == colonne) && i != colonne) {
			data.push_back(line);
		}
	}
	
	//colonne 9 (8) 36 x 23 (cases tableau
	
}

void Env::setPenteCsv() { 
	string filename = "donnée-cours-d'eau.csv"
	int x_size = 36;
	int y_size = 23;
	
	readCsv(x_size, y_size, filename);
}	

void Env::initTableau(int largeur, int hauteur, int longueur) {
	
	//tableau de structure en 3D
	int grandeur = hauteur * longueur * largeur;
	
	// z vers le haut, y vers la largeur, x vers la longueur
	int i = (z * (largeur) + y) + largeur * hauteur * x;

	/* double pente();
	double h_eau = hauteur_eau(pente, debit); */

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
}

#include <iostream>
#include "Env.hpp"


Env::Env(int largeur, int hauteur, int longueur)
	:largeur_(largeur), hauteur_(hauteur), longueur_(longueur) 
{
	init_tableau(largeur_, hauteur_, longueur_); 
	// initie le tableau représentant la rivière
}


void Env::init_tableau(int largeur, int hauteur, int longueur) {
	
	int grandeur = hauteur * longueur * largeur;
	//tableau de structure en 3D
	int i = (z * (largeur) + y) + largeur * hauteur * x;
	// z vers le haut, y vers la largeur, x vers la longueur

	case * tableau = new case[hauteur*largeur*longueur];

	//initialisation du tableau
	int pente = 0.06; // basé sur la pente moyenne du rhône

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

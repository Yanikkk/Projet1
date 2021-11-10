#include <stdbool.h> // inclut le type booléen
//modélisation d'un tableau malloc en 3D
#include "main.h"
#include "case.c"
#include "matiere.c"
#include "eau.c"
#include "sol.c"
#include "air.c"
//tableau initialiser
// largeur

int largeur = 2000; // y
int hauteur = 3000; // z
int longeur = 20000; // x

// demander à l'utilisateur les param (en [m] -> on mettra en cm?
int grandeur = hauteur * longeur * largeur;
//tableau de structure en 3D
int = y * hauteur + z + largeur * hauteur * x;
// z vers le haut, y vers la largeur, x vers la longueur
int i = (z * (largeur) + y) + largeur * hauteur * x;

struct case* model = malloc(grandeur * sizeof(double));

//initialisation du tableau
int state = 0;
int pente = 0.06; //basé sur la pente moyenne du rhône
verfie_pente(pente); // fonction main véréfie qu il reste du sol en aval
int h_eau;
int h_sol = 3/4 * hauteur; // initialement
int x = 0;
int y = 0;
int z = 0;
// pente réaliste , comment remplir le sol
//la hauteur_eau trouver sa formule (simplifier)
//idée hauteur => comment? débit fixe puis on définit h, ou inverse
// du coup quand est ce qu'on définit une vitesse à l'eau
//couleur de chaque case?
// si on définit une pente le faire mtn non?
// fonction faire avancer l'eau tout les pas de temps x
//fonctions pour initialiser le tableau ?
// fonctiopns pour initialiser les coordonnées
for(int i = 0; i <= grandeur; i++){
	calcul_pente(h_sol
	y =+ 1;
	if(i == (largeur-1) + z * largeur + x * largeur + hauteur){ // à chaque largeur finit, on monte dans le tableau
		z =+1;
		y = 0;
	}
	if(z == hauteur + 1){//une fois le haut du tableau atteint
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

#include <iostream>
#include <random>

#include "Sol.hpp"


Sol::Sol(Env * env_param, std::string type, double vitesse)
	:Matiere(env_param, type, vitesse){}/*, argument propre à sol*/

void Sol::setCouleur() {
	int taille_sol = getEnv2()->getH_sol();
	int hauteur_case = getEnv2()->getHauteur();
	// changer getEnv2()->getHauteur() comme pour l'eau
	
// si on fait par rapport à la taille du sol ca ira pas parce que c'est pas la même partout

	if (hauteur_case > 0.75*taille_sol) {
		//couleur aléatoire entre 75 et 100
	} else if (hauteur_case > 0.5*taille_sol) {
		//couleur aléatoire entre 50 et 75
	} else if (hauteur_case > 0.25*taille_sol) {
		//couleur aléatoire entre 25 et 50
	} else {
		//couleur aléatoire entre 0 et 25
	} 
}
// Pas vraiment faites mais facil une fois que ça marchera pour l'eau casi pareil

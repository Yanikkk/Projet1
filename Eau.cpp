#include <iostream>
#include <math.h> //pas déjà include?
#include <random>

#include "Eau.hpp"


Eau::Eau(Env* env_param, std::string type, int profondeur, double vitesse)
	:Matiere(env_param, type, vitesse), profondeur_(profondeur)
{
	setVitesse();
	setCouleur(); // il passe aussi dans le setCouleur de matière avant... 
	// je sais pas comment faire dans le constructeur de matiere pour qu'il vienne dans le set couleur de la sous-classe en question
} 

void Eau::setVitesse() {

	double Ks = 30.0; 
	double S = (getEnv2()->getH_eau() - getEnv2()->getH_sol()) * getEnv2()->getLargeur(); 
	double P = getEnv2()->getLargeur() + 2 * (getEnv2()->getH_eau() - getEnv2()->getH_sol());
	double R = S/P;
	//arrondir autrement? (enlève juste après la , => n'arrondis pas)
	int pente_arrondie = getEnv2()->getPente();
	double I = pente_arrondie/100.0; //tout en [m]
	//formule de Manning Strickler 
	vitesse_ = Ks * pow(R, 2.0/3.0) * pow(I, 1.0/2.0);
	// on arrondi la vitesse à deux chiffres après la virgule
	//vitesse_ =  faire une fonction arrondir?
}
/*
double Eau::getVitesse() const{
	return vitesse_;
}s
*/

// Pas le override en cpp ? 
void Eau::setCouleur() {
	int taille_eau = getEnv2()->getH_eau() - getEnv2()->getH_sol();
	// int hauteur_case = getEnv2()->getZ() - getEnv2()->getH_sol(); -> on a profondeur maintenant 
	// a la place de getEnv2()->getHauteur() c'est getZ non ? getHauteur c'est la hauteur de la simulation. comment chercher getZ ? this.getZ() ? 
	
	//remettre constexpr int si on trouve comment mettre c++11 ?
	int MIN; 
	int MAX; 
	std::random_device rd;
    std::default_random_engine eng(rd());
    //std::cout << "setCouleur de eau" << std::endl;

	// voir si les if joue vu que c'est des int sinon mettre des doubles ça sera quand même juste.
	// vérifier aussi si quand c'est proche de 100 c'est foncé ou claire, au pire juste changer les chiffres.
	if (profondeur_ >= 0.75*taille_eau) {
		MIN = 25;
		MAX = 50;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (profondeur_ >= 0.5*taille_eau) {
		MIN = 40;
		MAX = 70;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (profondeur_ >= 0.25*taille_eau) {
		MIN = 60;
		MAX = 90;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else {
		MIN = 80;
		MAX = 100;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} 
}

void Eau::setProfondeur(int actuelle){
	profondeur_ =	actuelle;
}













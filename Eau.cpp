#include <iostream>
#include <math.h> //pas déjà include?
#include <random>

#include "Eau.hpp"


Eau::Eau(Env* env_param, std::string type, int profondeur, double vitesse, Polluant* polluant)
	:Matiere(env_param, type, vitesse), profondeur_(profondeur), polluant_(polluant)
{
	setVitesse();
	setCouleur(); 
} 

void Eau::setVitesse() {

	double Ks = 30.0; 
	double S = (getEnv2()->getH_eau() - getEnv2()->getH_sol()) * getEnv2()->getLargeur(); 
	double P = getEnv2()->getLargeur() + 2 * (getEnv2()->getH_eau() - getEnv2()->getH_sol());
	double R = S/P;
	int pente_arrondie = getEnv2()->getPente();
	double I = pente_arrondie/100.0; ///< tout en [m] 
	vitesse_ = Ks * pow(R, 2.0/3.0) * pow(I, 1.0/2.0); ///< formule de Manning Strickler 
}
/*
double Eau::getVitesse() const{
	return vitesse_;
}s
*/
 
void Eau::setCouleur() {
	int taille_eau = getEnv2()->getH_eau() - getEnv2()->getH_sol();

	//remettre constexpr int si on trouve comment mettre c++11 ????????????????????????????????????????????????
	int MIN; 
	int MAX; 
	std::random_device rd;
    std::default_random_engine eng(rd());

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

void Eau::setPolluant(std::string nom, double masse, int depot_x, double vitesse){
	if(nom == "nullptr"){
		polluant_ = nullptr;
	}else{
		polluant_ = new Polluant(nom, masse, depot_x, vitesse);
	}
}

void Eau::setProfondeur(int actuelle){
	profondeur_ = actuelle;
}

int Eau::getProfondeur() const{
	return profondeur_;
}

Polluant* Eau::getPolluant() const{
	return polluant_;
}











#include <iostream>
#include <math.h> //pas déjà include?

#include "Eau.hpp"


Eau::Eau(Env* env_param, std::string type, double vitesse)
	:Matiere(env_param, type, vitesse)/*, argument propre à eau */
{
	setVitesse();
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

double Eau::getVitesse() const{
	return vitesse_;
}

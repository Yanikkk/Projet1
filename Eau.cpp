#include <iostream>
#include <math.h> //pas déjà include?

#include "Eau.hpp"


Eau::Eau(Env* env_param)
	:Matiere(env_param)/*, argument propre à eau */
{
	setVitesse();
} 


void Eau::setVitesse() {
	
	// Je sais pas si faut mettre des doubles...
	double Ks = 30.0; 
	double S = (getEnv2()->getH_eau() - getEnv2()->getH_sol()) * getEnv2()->getLargeur(); 
	double P = getEnv2()->getLargeur() + 2 * (getEnv2()->getH_eau() - getEnv2()->getH_sol());
	double R = S/P;
	double I = getEnv2()->getPente()/100.0; //tout en [m]
	//formule de Manning Strickler 
	vitesse_ = Ks * pow(R, 2.0/3.0) * pow(I, 1.0/2.0);
}

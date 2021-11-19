#include <iostream>
#include <math.h> //pas déjà include?

#include "Eau.hpp"


Eau::Eau()
	:Matiere()/*, argument propre à eau */
{
	setVitesse();
	
	/*vitesse_ = 30 * pow(((env2->getH_eau()-getEnv2()->getH_sol())*getEnv2()->getLargeur())/(getEnv2()->getLargeur() + 2 * (getEnv2()->getH_eau()-getEnv2()->getH_sol())),2/3)
	 *  * pow(getEnv2()->getPente(), 1/2);*/
} 


void Eau::setVitesse() {
	
	// Je sais pas si faut mettre des doubles...
	int Ks = 30; 
	int S = (env2->getH_eau() - env2->getH_sol()) * env2->getLargeur(); // j'étais plus sur de ce qu'on met entre env2-> ou getEnv2()->
	int P = env2->getLargeur() + 2 * (env2->getH_eau() - env2->getH_sol());
	int R = S/P;
	int I = env2->getPente(); //voir les unité de la pente en ° en %,...
	
	//formule de Manning Strickler 
	vitesse_ = Ks * pow(R, 2/3) * pow(I, 1/2); // y'a pas sqr pour la racine ? 
}

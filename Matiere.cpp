#include <iostream>

#include "Matiere.hpp"


Matiere::Matiere(Env* env_param)
	{
		env2 = env_param;
	}

void Matiere::setEnv2(Env* env){
	env2 = env;
}

Env* Matiere::getEnv2() const{
	return env2;
}

/*void Matiere::setCouleur(const sf::color value) {
	couleur = value;
}	
	
sf::color Matiere::getCouleur() const {
	return couleur;
}
*/

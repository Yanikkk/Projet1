#include <iostream>

#include "Matiere.hpp"


Matiere::Matiere(Env* env_param, std::string type, double vitesse)
		:env2(env_param), type_(type), vitesse_(vitesse)
	{
		setCouleur();
		//Comme le constructeur de matiere est appelé dans celui de chaque matière et que setCouleur est virtual, la couleur sera set avec la fonction setCouleur de la matière (si redéfinie).
	}

void Matiere::setEnv2(Env* env){
	env2 = env;
}

Env* Matiere::getEnv2() const{
	return env2;
}

std::string Matiere::getType() const{
	std::cout << "Matiere_a" << std::endl;
	return type_;
}

void Matiere::setType(std::string nom){
		type_ = nom;
}

double Matiere::getVitesse() const {
	return vitesse_;
}
/*
int Matiere::getCouleur() const {
	return couleur_;
}

void Matiere::setCouleur() {
	couleur_ = 0;
	// voir ce qu'on met par défaut -> dans notre cas c'est l'air qui va utiliser celle la.
	//Mais ducoup faut associer une cmap à l'air sinon pas de sens.
	// A voir comment on défini la couleur en général.
}
*/

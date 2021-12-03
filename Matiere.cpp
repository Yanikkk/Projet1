#include <iostream>

#include "Matiere.hpp"


Matiere::Matiere(Env* env_param, std::string type, double vitesse)
		:env2(env_param), type_(type), vitesse_(vitesse)
	{}

void Matiere::setEnv2(Env* env){
	env2 = env;
}

Env* Matiere::getEnv2() const{
	return env2;
}

std::string Matiere::getType() const{
	return type_;
}

double Matiere::getVitesse() const{
	return vitesse_;
}


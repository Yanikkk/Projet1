#include <iostream>

#include "Matiere.hpp"


Matiere::Matiere(Env* env_param, std::string type, double vitesse)
	: env2(env_param), type_(type), vitesse_(vitesse) {}

void Matiere::setEnv2(Env* env){
	env2 = env;
}

void Matiere::setType(std::string nom){
		type_ = nom;
}

Env* Matiere::getEnv2() const{
	return env2;
}

std::string Matiere::getType() const{

	return type_;
}

double Matiere::getVitesse() const {
	return vitesse_;
}

int Matiere::getCouleur() const {
	return couleur_;
}

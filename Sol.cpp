#include <iostream>
#include <random>

#include "Sol.hpp"


Sol::Sol(Env * env_param, std::string type, int profondeur, double vitesse)
	:Matiere(env_param, type, vitesse), profondeur_(profondeur) 
{
	setCouleur();
}

void Sol::setCouleur() {
	int taille_sol = getEnv2()->getH_sol();
	//remettre constexpr int si on trouve comment mettre c++11 ???????????????????????????????????????????????
	int MIN; 
	int MAX; 
	std::random_device rd;
    std::default_random_engine eng(rd());

	if (taille_sol - profondeur_ < 2) {
		MIN = 15;
		MAX = 35;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);	
	} else if (taille_sol - profondeur_ < 4) {
		MIN = 30;
		MAX = 50;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (taille_sol - profondeur_ < 6) {
		MIN = 45;
		MAX = 60;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else {
		MIN = 55;
		MAX = 70;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} 
}
/*
Polluant* getPolluant() const{
	return polluant_;
}*/
// Pas vraiment faites mais facil une fois que ça marchera pour l'eau casi pareil


#include <iostream>
#include <random>

#include "Sol.hpp"


Sol::Sol(Env * env_param, std::string type, int profondeur, double vitesse)
	:Matiere(env_param, type, vitesse), profondeur_(profondeur) 
{
	
	std::cout << env_param << std::endl;
	setCouleur();
}

void Sol::setCouleur() {
	int taille_sol = getEnv2()->getH_sol();
	
	//remettre constexpr int si on trouve comment mettre c++11 ?
	int MIN; 
	int MAX; 
	std::random_device rd;
    std::default_random_engine eng(rd());

	if (profondeur_ > 0.75*taille_sol) {
		MIN = 25;
		MAX = 45;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);	
	} else if (profondeur_ > 0.5*taille_sol) {
		MIN = 40;
		MAX = 60;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (profondeur_ > 0.25*taille_sol) {
		MIN = 55;
		MAX = 70;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else {
		MIN = 65;
		MAX = 80;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} 
}
// Pas vraiment faites mais facil une fois que ça marchera pour l'eau casi pareil


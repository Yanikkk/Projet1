#include <iostream>
#include "Air.hpp"


Air::Air(Env* env_param, std::string type, double vitesse)
	:Matiere(env_param, type, vitesse)
{
	setCouleur();
}

void Air::setCouleur() {
	couleur_ = 35;
}


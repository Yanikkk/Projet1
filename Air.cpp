#include <iostream>
#include "Air.hpp"


Air::Air(Env* env_param, std::string type, double vitesse)
	:Matiere(env_param, type, vitesse)
{
	setCouleur();
}


void Air::setCouleur() {

	couleur_ = 30;
	/* 
	if ((GetKeyState(112) & 0x8000) == 1) { // p luie
		couleur_ = 15;	
	} else if ((GetKeyState(98) & 0x8000) == 1) { // b rouillard
		couleur_ = 100;
	} else if ((GetKeyState(110) & 0x8000) == 1) { // n uit
		couleur_ = 0;
	} else if ((GetKeyState(114) & 0x8000) == 1) { // sun r ise
		couleur_ = 90;
	} else if ((GetKeyState(115) & 0x8000) == 1) { // sun s et
		couleur_ = 75;
	}
	// peut-être pas besoin les == 1
	*/
}


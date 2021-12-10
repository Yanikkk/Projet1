#include <iostream>
#include "Air.hpp"


Air::Air(Env* env_param, std::string type, double vitesse)
	:Matiere(env_param, type, vitesse)
{
	setMeteo();
}


void Air::setMeteo() {
		
	meteo_ = "sky";

	if ((GetKeyState(112) & 0x8000) == 1) { // p
		meteo_ = "pluie";	
	} else if ((GetKeyState(98) & 0x8000) == 1) { // b 
		meteo = "brouillard";
	} else if ((GetKeyState(110) & 0x8000) == 1) { // n
		meteo = "nuit";
	} else if ((GetKeyState(114) & 0x8000) == 1) { // r
		meteo = "sunrise";
	} else if ((GetKeyState(115) & 0x8000) == 1) { // s
		meteo = "sunset";
	}
	// peut-être pas besoin les == 1
}

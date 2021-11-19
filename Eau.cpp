#include <iostream>
#include <math.h> //pas déjà include?
#include "Eau.hpp"


Eau::Eau()
	:Matiere()/*, argument propre à eau */
{
	//formule de Manning Strickler voir drive
	vitesse_ = 30 * pow(((env2->getH_eau()-getEnv2()->getH_sol())*getEnv2()->getLargeur())/(getEnv2()->getLargeur() + 2 * (getEnv2()->getH_eau()-getEnv2()->getH_sol())),2/3) * pow(getEnv2()->getPente(), 1/2);
	
} 

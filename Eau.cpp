#include <iostream>
#include "Eau.hpp"
#include <math.h> //pas déjà include?


Eau::Eau()
	:Matiere()
	{
		//formule de Manning Strickler voir drive
		vitesse_ = 30 * pow((getH_eau-getH_sol)/(getLargeur + 2 * (getH_eau-getH_sol)),2/3) * pow(getPente, 1/2);
	} /*, argument propre à eau*/

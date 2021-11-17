#include <iostream>
#include <math.h> //pas déjà include?
#include "Eau.hpp"


Eau::Eau()
	:Matiere()/*, argument propre à eau */
{
	//formule de Manning Strickler voir drive
	vitesse_ = 30 * pow((getH_eau()-getH_sol())/* j'ajouterais " *getLargeur() " *//(getLargeur() + 2 * (getH_eau()-getH_sol())),2/3) * pow(getPente(), 1/2);
} 

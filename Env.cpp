#include <iostream>
#include "Env.hpp"


Env::Env(int largeur, int hauteur, int longueur)
	:largeur_(largeur), hauteur_(hauteur), longueur_(longueur) 
{
	init_tableau(largeur_, hauteur_, longueur_); 
	// initie le tableau représentant la rivière
}

#include <iostream>

#include "PolluantB.hpp"

PolluantB::PolluantB(double facteur_dilution, std::string nom, std::string nom_cmap) 
	: Polluant(facteur_dilution, nom, nom_cmap) {}

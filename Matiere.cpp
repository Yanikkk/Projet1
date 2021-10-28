#include <iostream>
#include "Matiere.hpp"


Matiere::Matiere()

void Matiere::setCouleur(const sf::color value) {
	couleur = value;
}	
	
sf::color Matiere::getCouleur() const {
	return couleur;
}

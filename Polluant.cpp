#include <iostream>

#include "Polluant.hpp"

Polluant::Polluant(std::string nom, int etat_dilution_) 
	: nom_(nom), etat_dilution_(etat_dilution)
{
	setPolluant(nom);
}


void Polluant::setPolluant(std::string nom) {
	
	switch (nom) {
		case "fer" : 
			nom_cmap_ = "Reds"	
			facteur_dilution_ = 1.0;
					
			break; 
		case "algue" : 
			nom_cmap_ = "Greens"	
			facteur_dilution_ = 1.0;
					
			break; 
		case "boue" : 
			nom_cmap_ = "copper"	
			facteur_dilution_ = 1.0;

			break; 
		case "petrole" : 
			nom_cmap_ = "Greys"	
			facteur_dilution_ = 1.0;
					
			break; 
		default : 
			nom_cmap_ = "binary"	
			facteur_dilution_ = 1.0;
	}
}

double Polluant::getDilution() const {
	return etat_dilution_;
} 

double Polluant::getFacteurDilution() const {
	return facteur_dilution_;
} 

std::string Polluant::getNom() const {
	return nom_;
} 

std::string Polluant::getNomCmap() const {
	return nom_cmap_;
} 

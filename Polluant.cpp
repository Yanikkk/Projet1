#include <iostream>
#include "Polluant.hpp"
using namespace std;

Polluant::Polluant(std::string nom, int dilution, double masse, int depot_x) 
	: nom_(nom), etat_dilution_(dilution), masse_(masse), depot_x_(depot_x)
{
	setPolluant(nom);
}


void Polluant::setPolluant(std::string nom) {
	int type = 0;
	enum pollution{fer = 1, phosphate = 2, amonia = 3};
	if( nom == "fer"){
		type = 1;
	}
	switch (type) 
	{
		case fer : 
			nom_cmap_ = "Reds";
			coeff_dispersion_ = 0.5;
				
			break; 
		case phosphate : 
			nom_cmap_ = "Greens";	
			coeff_dispersion_ = 1.0;
					
			break; 
		case amonia : 
			nom_cmap_ = "copper";	
			coeff_dispersion_ = 0.8;

			break; 
		/*case "petrole" : 
			nom_cmap_ = "Greys"	
			coeff_dispersion_ = 1.0;
					
			break; 
		default :  //polluant inconnue facteur de dilution aux hasards
			nom_cmap_ = "binary"	
			coeff_dispersion_ = 1.0;
	*/
	}
}

double Polluant::getDilution() const {
	return etat_dilution_;
} 

double Polluant::getCoeffDispersion() const {
	return coeff_dispersion_;
} 

std::string Polluant::getNom() const {
	return nom_;
} 

std::string Polluant::getNomCmap() const {
	return nom_cmap_;
} 

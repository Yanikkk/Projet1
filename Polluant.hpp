#ifndef POLLUANT_HPP
#define POLLUANT_HPP

#pragma once

#include "Eau.hpp"

/*!
 * @class Polluant
 */
class Polluant : {
public : 

    /*!
     * @brief constructeur
     *
     * @param .........
     */
	Polluant(std::string nom, int etat_dilution_);
	
	void setPolluant(std::string nom);  
	
	int getDilution() const; 
		
	double getFacteurDilution() const;
	
	std::string getNom() const; 
	
	std::string getNomCmap() const;
	 		
private : 

double facteur_dilution_;
int etat_dilution_;			///< augmenter l'etat de dilution quand il se propage
std::string nom_;
std::string nom_cmap_;
}; 

#endif // POLLUANT_HPP


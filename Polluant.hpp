#ifndef POLLUANT_HPP
#define POLLUANT_HPP

#pragma once

/*!
 * @class Polluant
 */
class Polluant{
public : 

    /*!
     * @brief constructeur
     *
     * @param .........
     */
	Polluant(std::string nom, int etat_dilution_);
	
	void setPolluant(std::string nom);  
	
	double getDilution() const; 
		
	double getCoeffDispersion() const;
	
	std::string getNom() const; 
	
	std::string getNomCmap() const;
	 		
private : 
//coefficient de dispersion
//longitudinale, paramètre essentiel pour pouvoir prédire avec précision l’évolution spatiotemporelle d’un polluant dans un cours d’eau au moyen de l’Equation d’Advection
//Dispersion. 

//https://tel.archives-ouvertes.fr/tel-00218245v2/document
// facteur_dispersion_longitudinale = 0.058 *(H*U)/S
//H = hauteur d'eau (m)
// U = vitesse moyen du courant (m/s)
//S = pente (m/m)
//schéma => p.38 et 39
//
//formule selon x p49 (compliqué)
//
//coefficient de dispersion latéral(z et y)
//E = 0,15HU* -[m2/s]
//H = hauteur d'eau[m]
//U* = vitesse de cisaillement[m/s] 
//(p.148) en const on va mettre entre 0.053+-0.031

double coeff_dispersion_;
//sa concentration en % 1 = 100%
double etat_dilution_;			///< augmenter l'etat de dilution quand il se propage
std::string nom_;
std::string nom_cmap_;
}; 

#endif // POLLUANT_HPP


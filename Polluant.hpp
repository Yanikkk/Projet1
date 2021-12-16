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
	Polluant(std::string nom = "Inconnu", double masse = 0, int depot_x = 0, double vitesse = 0);
	
	void setPolluant(std::string nom);  
	
	double getDilution() const; 
		
	double getCoeffDispersion() const;
	
	double getMasse() const;
	
	void setMasse(double);
	
	double getVitesse() const;
	
	int getCaseDepart() const;
	
	void setCouleur();
	
	int getCouleur() const;
	
	std::string getNom() const; 
	
	std::string getNomCmap() const;
	 		
private : 
/*!-------------------------------------
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
*/
double masse_; //[kg]
double vitesse_; //[m/s]
//coeff de dispersion 0-1
//plus il est élevé moins il se disperse
//dans des cases différentes(1-10)
double coeff_dispersion_;
std::string nom_;
std::string nom_cmap_;
//où le polluat est déposé en x
int depot_x_;
int couleur_;

}; 

#endif // POLLUANT_HPP


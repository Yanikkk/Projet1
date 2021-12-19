#ifndef POLLUANT_HPP
#define POLLUANT_HPP

#pragma once

/*!
 * @class Polluant
 * 
 * @brief C'est un attribut de le la classe Eau. L'eau peut contenir un polluant.
 */
class Polluant{
public : 

    /*!
     * @brief constructeur
     *
     * @param nom; nom du polluant
     * @param masse; masse du polluant
     * @param depot_x; case où débute le polluant
     * @param vitesse; vitesse du polluant
     */
	Polluant(std::string nom = "Inconnu", double masse = 0, int depot_x = 0, double vitesse = 0);
	
    /*!
     * @brief les setters (méthodes set) permettent de mettre à jour l'attribut de la classe en dehors de cette dernière
     * 
     * @param nom, nouvelle_m; sont les nouvelles valeurs attribuées aux attributs de Case.
     */
	void setPolluant(std::string nom); 
	void setMasse(double nouvelle_m);
	
	/*!
     * @brief initie la couleur du polluant par rapport à sa concentration. 
     */	
	void setCouleur(); 

	/*!
     * @brief Les getters (méthodes get) permettent d'accéder aux attributs privés de cette classe en dehors de cette dernière.
     *
     * Elles sont définies const car elles ne modifient pas d'attributs de la classe.
     *
     * @return Elles retournent les attributs privé de la classe
     */	
	double getMasse() const;
	double getVitesse() const;	
	double getCoeffDispersion() const;
	std::string getNom() const; 
	std::string getNomCmap() const;
	int getCaseDepart() const;
	int getCouleur() const;
	 		
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
double masse_;				///< masse de polluant en [kg]
double vitesse_; 			///< vitesse du polluant en [m/s] ???????????????????????????????????????? SERT A QQCH ?  VU QU'ELLE AVANCE COMME L'EAU ???????????????????????????????????
double coeff_dispersion_;   ///< coefficient de dispersion du polluant entre 0 et 1 (plus il est élevé, moins il se disperse)
std::string nom_;			///< nom du polluant
std::string nom_cmap_;		///< gamme de couleur du polluant
int depot_x_;				///< case d'entrée du polluant
int couleur_;				///< coulezr du polluant

}; 

#endif // POLLUANT_HPP


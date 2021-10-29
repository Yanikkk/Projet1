#ifndef ENV_HPP
#define ENV_HPP

#pragma once

#include "Case.hpp"

/*!
 * @class Env
 */

class Env : {
public : 

    /*!
     * @brief constructeur
     *
     * @param largeur; nombre de case dans le tableau représentant la largeur de la rivière
     * @param hauteur; nombre de case dans le tableau représentant la hauteur de la rivière
     * @param longueur; nombre de case dans le tableau représentant la longueur de la rivière
     */
	Env(int largeur, int hauteur, int longueur);
	
	/*!
     * @brief permet de modifier la pente de l'environnement
     *
     * @param value; sera la nouvelle valeure de l'attribut pente.
     */
	void setPente(const double value);
	
	
	/*!
     * @brief initie le tableau représentant la rivière
     *
     * @param largeur; nombre de case dans le tableau représentant la largeur de la rivière
     * @param hauteur; nombre de case dans le tableau représentant la hauteur de la rivière
     * @param longueur; nombre de case dans le tableau représentant la longueur de la rivière
     */
	void init_tableau(int largeur, int hauteur, int longueur)
	
		
private : 

	int largeur_; 		///< largeur de la rivière
	int hauteur_;  	    ///< hauteur de la rivière 
	int longueur_;      ///< lonugueur de la rivière
	double pente_;		///< pente du fond de la rivière 
	int debit_;			///< débit de la rivière
	Case* tableau_;		///< tableau contenant des pointeurs sur des cases
}; 

#endif // Env_HPP

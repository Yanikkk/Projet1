#ifndef ENV_HPP
#define ENV_HPP

#pragma once

#include "Matiere.hpp" // ???? ou exactement ? dans cpp plutot peut être ???????????????

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
		
	
private : 

	int largeur_; 		///< largeur de la rivière
	int hauteur_;  	    ///< hauteur de la rivière 
	int longueur_;      ///< lonugueur de la rivière
}; 

#endif // Env_HPP

#ifndef EAU_HPP
#define EAU_HPP

#pragma once
#include "Matiere.hpp"
#include "Env.hpp"

/*!
 * @class Eau
 * 
 * Sous-classe de la classe mère Matiere car l'eau EST UNE matiere.
 * 
 * Cette classe doit redéfinir les fonctions suivantes : ........ -> elles seront override (précise qu'elles sont redéfinies)
 */

class Eau : public Matiere {
public : 

    /*!
     * @brief constructeur
     *
     * @param ........
     */
	Eau();
		
	
private : 
	double vitesse_;      ///< Vitesse de l'eau 
}; 

#endif // EAU_HPP

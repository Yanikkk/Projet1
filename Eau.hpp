#ifndef EAU_HPP
#define EAU_HPP

#pragma once
#include "Matiere.hpp"


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
	double vitesse_;

}; 

#endif // EAU_HPP

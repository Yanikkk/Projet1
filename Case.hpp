#ifndef CASE_HPP
#define CASE_HPP

#pragma once

#include "Matiere.hpp"

/*!
 * @class Case
 */

class Case {
public : 

    /*!
     * @brief constructeur
     *
     * @param x, y et z sont les coordonées du tableau représentant la rivière, respectivement la longueur, la largeur et la hauteur.
     */
	Case(int x, int y, int z);
		
	
private :

	int x_;
	int y_;
	int z_;
	Matiere matiere_; 
}; 

#endif // CASE_HPP

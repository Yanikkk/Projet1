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
     * @param ..........
     */
	Case();
		
	
private :

	int x_;
	int y_;
	int z_;
	Matiere matiere_; 
}; 

#endif // CASE_HPP

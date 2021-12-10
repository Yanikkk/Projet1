#ifndef POLLUANTB_HPP
#define POLLUANTB_HPP

#pragma once

#include "Polluant.hpp"

/*!
 * @class PolluantB
 */
class PolluantB : public Polluant {
public : 

    /*!
     * @brief constructeur
     *
     * @param .........
     */
	PolluantB(double facteur_dilution, std::string nom, std::string nom_cmap = "bone");
		
private : 

}; 

#endif // POLLUANTB_HPP

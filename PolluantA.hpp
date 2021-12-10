#ifndef POLLUANTA_HPP
#define POLLUANTA_HPP

#pragma once

#include "Polluant.hpp"

/*!
 * @class PolluantA
 */
class PolluantA : public Polluant {
public : 

    /*!
     * @brief constructeur
     *
     * @param .........
     */
	PolluantA(double facteur_dilution, std::string nom, std::string nom_cmap = "gist_heat");
		
private : 

}; 

#endif // POLLUANTA_HPP

#ifndef SOL_HPP
#define SOL_HPP

#pragma once

#include "Matiere.hpp"

/*!
 * @class Sol
 * 
 * Sous-classe de la classe mère Matiere car le sol EST UNE matiere.
 * 
 * Cette classe doit redéfinir les fonctions suivantes : ........ -> elles seront override (précise qu'elles sont redéfinies)
 */
class Sol : public Matiere {
public : 

    /*!
     * @brief constructeur
     *
     * @param .........
     */
	Sol(Env* env_param = nullptr, std::string type = "SOL", double vitesse = 0.0);
		
	
private : 


}; 

#endif // SOL_HPP

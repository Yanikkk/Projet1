#ifndef AIR_HPP
#define AIR_HPP

#pragma once
#include "Matiere.hpp"
#include "Env.hpp"


/*!
 * @class Air
 * 
 * Sous-classe de la classe mère Matiere car l'air EST UNE matiere.
 * 
 * Cette classe doit redéfinir les fonctions suivantes : ........ -> elles seront override (précise qu'elles sont redéfinies)
 */
class Air : public Matiere {
public : 

    /*!
     * @brief constructeur
     *
     * @param ..........
     */
	Air(Env* env_param = nullptr, std::string type = "AIR", double vitesse = 0.0);
	
	//void setMeteo(); 
			
private : 

std::string meteo_ = "sky";
}; 

#endif // AIR_HPP

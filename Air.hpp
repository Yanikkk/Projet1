#ifndef AIR_HPP
#define AIR_HPP

#pragma once

#include "Matiere.hpp"
#include "Env.hpp"

/*!
 * @class Air
 * 
 * Sous-classe de la Super-classe Matiere car l'air EST UNE matiere.
 * 
 * Cette classe n'a pas de fonctions à redéfinir. 
 */
class Air : public Matiere {
public : 

    /*!
     * @brief constructeur
     *
     * @param env_param, type, vitesse; Ce sont les paramètres hérités de la super-classe.
     */
	Air(Env* env_param = nullptr, std::string type = "AIR", double vitesse = 0.0);
	
	/*!
     * @brief initie la couleur de l'air à une valeure constante de journée. 
     */	
	void setCouleur(); 
			
private : 

}; 

#endif // AIR_HPP

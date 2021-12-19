#ifndef SOL_HPP
#define SOL_HPP

#pragma once

#include "Matiere.hpp"
#include "Env.hpp"

/*!
 * @class Sol
 * 
 * Sous-classe de la Super-classe Matiere car le sol EST UNE matiere.
 * 
 * Cette classe n'a pas de fonctions à redéfinir.
 */
class Sol : public Matiere {
public : 

    /*!
     * @brief constructeur
     *
     * @param env_param, type, vitesse; Ce sont les paramètres hérités de la super-classe.
     * @param profondeur; Défini la profondeur de la case ou se situe la matiere 
     */
	Sol(Env* env_param = nullptr, std::string type = "SOL", int profondeur = 0, double vitesse = 0.0);
	
	/*!
     * @brief initie la couleur du sol par rapport à sa profondeur. 
     */	
	void setCouleur();
	
	//Polluant* getPolluant() const;
		
private : 

//Polluant* polluant_;
int profondeur_; ///< profondeur du sol (valeur plus élevée -> plus haute)
}; 

#endif // SOL_HPP

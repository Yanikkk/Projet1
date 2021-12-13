#ifndef SOL_HPP
#define SOL_HPP

#pragma once
#include "Polluant.hpp"
#include "Matiere.hpp"
#include "Env.hpp"
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
	Sol(Env* env_param = nullptr, std::string type = "SOL", int profondeur = 0, double vitesse = 0.0);
	
	void setCouleur() override;
	
	Polluant* getPolluant() const;
		
private : 

Polluant* polluant_;
int profondeur_;
}; 

#endif // SOL_HPP

#ifndef EAU_HPP
#define EAU_HPP

#pragma once
#include "Matiere.hpp"
#include "Env.hpp"

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
	Eau(Env* env_param = nullptr, std::string type = "EAU", int profondeur = 0, double vitesse = 0.0,Polluant* polluant = nullptr);
	
    /*!
     * @brief utilise la formule de Manning Strickler pour déterminer la vitesse de l'eau
     */	
	void setVitesse();
	
	void setCouleur();
	int getProfondeur() const;
	void setProfondeur(int);
	void setPolluant(std::string nom = "Inconnu", double masse = 0, int depot_x = 0, double vitesse = 0);
	Polluant* getPolluant()const;
	~Eau(){
		delete polluant_;
		polluant_ = nullptr;}
	
private : 

Polluant* polluant_;
int profondeur_;
}; 

#endif // EAU_HPP

#ifndef EAU_HPP
#define EAU_HPP

#pragma once

#include "Matiere.hpp"
#include "Env.hpp"

/*!
 * @class Eau
 * 
 * Sous-classe de la Super-classe Matiere car l'eau EST UNE matiere.
 * 
 * Cette classe n'a pas de fonctions à redéfinir. 
 */
class Eau : public Matiere {
public : 

    /*!
     * @brief constructeur
     *
     * @param env_param, type, vitesse; Ce sont les paramètres hérités de la super-classe.
     * @param profondeur; Défini la profondeur de la case ou se situe la matiere. 
     * @param polluant; Le polluant présent dans l'eau s'il y en a un.
     */
	Eau(Env* env_param = nullptr, std::string type = "EAU", int profondeur = 0, double vitesse = 0.0, Polluant* polluant = nullptr);
	
	/*!
     * @brief initie la vitesse de l'eau à l'aide de la formule de Manning Strickler
     */
	void setVitesse();
	
	/*!
     * @brief initie la couleur de l'eau par rapport à sa profondeur. 
     */	
	void setCouleur();
	
	/*!
     * @brief appel le constructeur de polluant avec les paramètres entrés en argument si le polluant existe
     * 
     * @param nom; nom du polluant
     * @param masse; masse initiale du polluant
     * @param depot_x; case ou est déposé le polluant
     * @param vitesse; vitesse du polluant
     */
	void setPolluant(std::string nom = "Inconnu", double masse = 0, int depot_x = 0, double vitesse = 0);
	
    /*!
     * @brief les setters (méthodes set) permettent de mettre à jour l'attribut de la classe en dehors de cette dernière
     *
     * @param actuelle; sont les nouvelles valeurs attribuées aux attributs de Case.
     */
	void setProfondeur(int actuelle);
	
	/*!
     * @brief Les getters (méthodes get) permettent d'accéder aux attributs privés de cette classe en dehors de cette dernière.
     *
     * Elles sont définies const car elles ne modifient pas d'attributs de la classe.
     *
     * @return Elles retournent les attributs privé de la classe
     */
	int getProfondeur() const;
	Polluant* getPolluant()const;

	/*!
     * @brief déstructeur de l'eau.
     */
	~Eau() {
		delete polluant_;
		polluant_ = nullptr;
	}
	
private : 

Polluant* polluant_; ///< polluant de l'eau
int profondeur_;	 ///< profondeur de l'eau (valeur plus élevée -> plus haute)
}; 

#endif // EAU_HPP

#ifndef MATIERE_HPP
#define MATIERE_HPP

#pragma once

#include "Polluant.hpp"

/*!
 * @brief pré-déclaration de la Classe Env
*/
class Env;

/*!
 * @class Matiere
 * 
 * @brief classe virtuelle car certaines fonctions sont virtuelles et peuvent être redéfinies dans des sous-classes. 
 * 
 * Il n'y a pas de méthode virtuelle pure, les sous-classes n'ont donc pas d'obligation de redéfinir des fonctions.
 * 
 * Super classe des différentes matières : eau, sol et air.
 */	
class Matiere {
public : 

    /*!
     * @brief constructeur
     *
     * @param env_param; C'est l'env auquel appartient la matière.
     * @param type; C'est le nom du type de matiere.
     * @param vitesse; La vitesse de la matiere.
     * 
     * @return La matiere fraichement créée
     */
	Matiere(Env* env_param = nullptr,std::string type = "vide", double vitesse = 0.0);
	
    /*!
     * @brief les setters (méthodes set) permettent de mettre à jour l'attribut de la classe en dehors de cette dernière
     *
     * @param env, nom; sont les nouvelles valeurs attribuées aux attributs de Case.
     */
	void setEnv2(Env* env);
	void setType(std::string nom);
	
	/*!
     * @brief Les getters (méthodes get) permettent d'accéder aux attributs privés de cette classe en dehors de cette dernière.
     *
     * Elles sont définies const car elles ne modifient pas d'attributs de la classe.
     *
     * @return Elles retournent les attributs privé de la classe
     */
	Env* getEnv2() const;
	std::string getType() const;
	double getVitesse() const;
	int getCouleur() const; 

	/*!
     * @brief déstructeur virtuel de Matiere
     */
	virtual ~Matiere(){}
	
protected : 
	
	Env* env2;			///< l'env auquel appartient la matière 
	std::string type_;  ///< type de matiere
	double vitesse_;	///< Vitesse de la matiere
	int couleur_; 		///< couleur de la matiere
}; 

#endif // MATIERE_HPP

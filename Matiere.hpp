#ifndef MATIERE_HPP
#define MATIERE_HPP

#pragma once

/*!
 * @class Matiere
 * 
 * @brief classe abstraite car des fonctions doivent être redéfinies. à vérifier ----> si y'a une virtuelle pure -> pas abstraite mais virtuelle non ? 
 * 
 * Les sous-classes doivent redéfinir ......... car elles ne peuvent pas être définies pour une matière quelconque. (virtual = 0) 
 * 
 * Super classe des différentes matières : eau, sol et air.
 */

class Matiere{
public : 

    /*!
     * @brief constructeur
     *
     * @param .........
     */
	Matiere();
	
	/*!
    * @brief permet de modifier la couleur d'une matière
    *
    * @param value nouvelle valeur que l'on souhaite associer à l'attribut couleur.
    */
    //void setCouleur(const sf::color value);	
		
	/*!
    * @brief Permet d'accéder à a couleur qui est un attribut privé 
    *
    * @return la couleur de la matière.
    */	
	//sf::color getCouleur() const;
	
private : 


//sf::color couleur; // voir comment on peut faire la couleure, peut être qu'il faudra plûtot choisir en python quand on fait le graph -> sinon la sf je sais plus... il faut créer une classe couleur maybe (internet)

}; 

#endif // MATIERE_HPP

#ifndef MATIERE_HPP
#define MATIERE_HPP

#pragma once

/*!
 * @brief pré-déclaration de la Classe Env
*/
class Env;

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
	Matiere(Env* env_param = nullptr,std::string type = "vide", double vitesse = 0.0);
	
	/*!
     * @brief Permet de modifier l'env
     *
     * @param env est la valeur passé à l'attribut env2 de cette classe.
     */
	void setEnv2(Env* env);
	
	/*!
     * @brief permet d'accéder à l'attribut env2
     *
     * constante car ne modifie pas d'attributs
     */
	Env* getEnv2() const;
	
	std::string getType() const;
	
	virtual double getVitesse() const;
	
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
	
protected : 
	
	Env* env2;
	std::string type_;
	double vitesse_;
//sf::color couleur; // voir comment on peut faire la couleure, peut être qu'il faudra plûtot choisir en python quand on fait le graph -> sinon la sf je sais plus... il faut créer une classe couleur maybe (internet)

}; 

#endif // MATIERE_HPP

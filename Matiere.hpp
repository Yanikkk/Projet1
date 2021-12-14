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
	
	void setType(std::string);
	
	virtual double getVitesse() const;
	// enlever le virtual non ? on a changé
	
	int getCouleur() const; 
	virtual void setPolluant(std::string, int);
	virtual Polluant* getPolluant()const;
	virtual void setProfondeur(int);
	virtual void setCouleur();
	virtual int getProfondeur() const;
	virtual ~Matiere(){}
	
protected : 
	
	Env* env2;
	std::string type_;
	double vitesse_;
	int couleur_; 

}; 

#endif // MATIERE_HPP

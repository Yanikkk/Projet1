#ifndef CASE_HPP
#define CASE_HPP

#pragma once

#include "Matiere.hpp"

/*!
 * @brief pré-déclaration de la Classe Env
 */
class Env;

/*!
 * @class Case
 */

class Case {
public : 

    /*!
     * @brief constructeur
     *
     * @param x, y et z sont les coordonées du tableau représentant la rivière, respectivement la longueur, la largeur et la hauteur.
     */
	Case(int x = 0, int y = 0, int z = 0);
	
	
	void setX(int x);
	void setY(int y);
	void setZ(int z);
	/*!
     * @brief Permet de définir la matiere par rapport aux coordonées
     */
	void setMatiere();
	
private :
	
	int x_;				///< coordonée x de la case
	int y_;				///< coordonée y de la case
	int z_;				///< coordonée z de la case
	Matiere matiere_; 	///< type de matière dans la case 
	Env* env;			///< l'env auquel appartient la case.

friend class Env;		///< La classe case peut accéder aux attribut privé de Env.
};

#endif // CASE_HPP

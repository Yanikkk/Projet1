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
 * 
 * @brief La class Env a un tableau de cette classe. Ce sont les éléments individuel de l'environnement.
 */
class Case {
public : 

    /*!
     * @brief constructeur
     *
     * @param x, y et z sont les coordonées du tableau représentant la rivière, respectivement la longueur, la largeur et la hauteur.
     */
	Case(int x = 0, int y = 0, int z = 0);
	
	/*!
     * @brief Permet de définir la matiere par rapport aux coordonées
     */
	void initMatiere();
	
    /*!
     * @brief permet de créer une nouvelle case d'eau
     *
     * @param w; indice de la case appelée.
     * @param profondeur; profondeur de la case w.
     * 
     * @return une nouvelle matière de type Eau.
     */
	Matiere* creation(int w, int profondeur);
	
    /*!
     * @brief les setters (méthodes set) permettent de mettre à jour l'attribut de la classe en dehors de cette dernière
     *
     * @param x, y, z, a; sont les nouvelles valeurs attribuées aux attributs de Case.
     */
	void setX(int x);
	void setY(int y);
	void setZ(int z);
	void setMatiere(Matiere* a);
	
	/*!
     * @brief Les getters (méthodes get) permettent d'accéder aux attributs privés de cette classe en dehors de cette dernière.
     *
     * Elles sont définies const car elles ne modifient pas d'attributs de la classe.
     *
     * @return Elles retournent les attributs privé de la classe
     */
	int getX() const;
	int getY() const;
	int getZ() const;
	Matiere* getMatiere() const;
	
private :
	
	int x_;				///< coordonée x de la case
	int y_;				///< coordonée y de la case
	int z_;				///< coordonée z de la case
	Matiere* matiere_; 	///< type de matière dans la case 
	Env* env;			///< l'env auquel appartient la case.

friend class Env;		///< La classe case peut accéder aux attribut privé de Env.
};

#endif // CASE_HPP

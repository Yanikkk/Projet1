#ifndef ENV_HPP
#define ENV_HPP

#pragma once 

#include <vector>
#include <string>

#include "Case.hpp"

using namespace std;

/*!
 * @class Env
 */

class Env {
public : 

    /*!
     * @brief constructeur
     *
     * @param largeur; nombre de case dans le tableau représentant la largeur de la rivière
     * @param hauteur; nombre de case dans le tableau représentant la hauteur de la rivière
     * @param longueur; nombre de case dans le tableau représentant la longueur de la rivière
     */
	Env(int largeur, int hauteur, int longueur);
	
	
	void writeCSV();
	
	/*!
     * @brief permet de modifier la pente de l'environnement
     *
     * @param value; sera la nouvelle valeure de l'attribut pente.
     */
	void setPenteCsv(std::string filename); //vérifier qu'on l'utilises
	
	
	/*!
     * @brief permet d'ouvrir et lire un fichier csv avec différents paramètre rentré en argument 
     *
     * @param x; nombre de colonne du fichier.
     * @param y; nombre de ligne du fichier.
     * @param filename; nom du fichier.
     * @param data; tableau dynamique de double dans lequel on souhaite stocker les valeurs désirées
     * @param colonne; colonne du fichier que l'on souhaite ajouter au tableau (-1 par défaut pour toutes les colonnes)
     * @param ligne; ligne du fichier que l'on souhaite ajouter au tableau (-1 par défaut pour toutes les lignes)
     */	
	
	void readCsv(int x, int y, std::string filename, std::vector<double*>& data, int colonne = -1, int ligne = -1);
	
	
	/*!
     * @brief initie le tableau représentant la rivière
     *
     * @param largeur; nombre de case dans le tableau représentant la largeur de la rivière
     * @param hauteur; nombre de case dans le tableau représentant la hauteur de la rivière
     * @param longueur; nombre de case dans le tableau représentant la longueur de la rivière
     */
	void initTableau(int hsol = -1, int heau = -1, double pente = -1);
	
	/*!
     * @brief Les méthodes get permettent d'accéder aux attributs privés de cette classe en dehors de celle-ci.
     *
     * Elles sont définies const car elles ne modifient pas d'attributs.
     * 
     * @return Elles retournent les attributs privé de la classe
     */
    int getLargeur() const;
	int getHauteur() const;
	int getH_eau() const;
	int getH_sol() const;
	int getPente() const;
		
private : 

	int largeur_; 		///< largeur de la rivière
	int hauteur_;  	    ///< hauteur de la rivière 
	int longueur_;      ///< lonugueur de la rivière
	int h_sol_;			///< hauteur du sol (en cases)
	int h_eau_;			///< hauteur de l'eau (en cases)
	double pente_;		///< pente du fond de la rivière 
	Case* tableau_;		///< tableau contenant des pointeurs sur des cases

}; 

#endif // Env_HPP

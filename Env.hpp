#ifndef ENV_HPP
#define ENV_HPP

#pragma once 

#include <vector>
#include <string>
using namespace std;

#include "Case.hpp"

/*!
 * @class Env
 * 
 * @brief C'est l'environnement de la rivière, c'est cette classe qui contient l'ensemble de case représentant la rivière
 */
class Env {
public : 

    /*!
     * @brief constructeur
     *
     * @param largeur; nombre de case dans le tableau représentant la largeur de la rivière
     * @param hauteur; nombre de case dans le tableau représentant la hauteur de la rivière
     * @param longueur; nombre de case dans le tableau représentant la longueur de la rivière
     * 
     * @return l'élément Env créé.
     */
	Env(int largeur, int hauteur, int longueur);
	
	/*!
     * @brief permet de copier tous les attributs de la classe dans un nouvel objet de type Env
     *
     * @param tampon; L'objet Env qui est copié
     */
	void copy(Env* tampon); // ????????????????????????????????????? CONSTRUCTEUR DE COPIE PAGE 22 COURS JAMILA -> MIEUX SI ON A LE TEMPS ?????????????????????????????????????????????
	
	/*!
     * @brief initie le tableau représentant la rivière
     *
     * @param largeur; nombre de case dans le tableau représentant la largeur de la rivière
     * @param hauteur; nombre de case dans le tableau représentant la hauteur de la rivière
     * @param longueur; nombre de case dans le tableau représentant la longueur de la rivière
     */
	void initTableau(int hsol = -1, int heau = -1, double pente = -1);

	/*!
     * @brief appel la méthode creation de la classe Case.
     *
     * @param w; indice de la case appelée.
     * @param profondeur; profondeur de la case w.
     * 
     * @return une nouvelle matière de type Eau.
     */
	Matiere* creation(int w, int profondeur); 	

	/*!
     * @brief permet d'ouvrir et lire un fichier csv avec différents paramètre rentré en argument
     *
     * @param x; nombre de colonne du fichier.
     * @param y; nombre de ligne du fichier.
     * @param filename; nom du fichier.
     * @param data; tableau dynamique de double dans lequel on souhaite stocker les valeurs désirées
     * @param colonne; colonne du fichier que l'on souhaite ajouter au tableau (-1 par défaut signifie que l'on veut lire toutes les colonnes)
     * @param ligne; ligne du fichier que l'on souhaite ajouter au tableau (-1 par défaut signifie que l'on veut lire toutes les lignes)
     */
	void readCsv(int x, int y, std::string filename, std::vector<double*>& data, int colonne = -1, int ligne = -1);

	/*!
     * @brief permet d'ouvrir et lire un fichier csv avec différents paramètre rentré en argument. Elle diffère de readCsv par le fait qu'ici, on souhaite obtenir des string et non des doubles.
     *
     * @param x; nombre de colonne du fichier.
     * @param y; nombre de ligne du fichier.
     * @param filename; nom du fichier.
     * @param data; tableau dynamique de string dans lequel on souhaite stocker les valeurs désirées
     * @param colonne; colonne du fichier que l'on souhaite ajouter au tableau (-1 par défaut signifie que l'on veut lire toutes les colonnes)
     * @param ligne; ligne du fichier que l'on souhaite ajouter au tableau (-1 par défaut signifie que l'on veut lire toutes les lignes)
     */
	void readCsvString(int x, int y, std::string filename, std::vector<std::string*>& data, int colonne = -1, int ligne = -1);	

	/*!
	 * @brief permet d'écrire un fichier csv contenant les coordonnées des cases contenant un polluant ainsi que le type de polluant et sa masse.
	 * Elle appel également affichePolluant(std::string)
	 * 
	 * @param filename; le nom du fichier csv créé. C'est ce même string qui sera dans l'appel à affichePolluant(std::string).
	 */
	void writeCSV(std::string filename);
	
	/*!
	 * @brief affiche les différentes quantités de polluants sur le terminal. appel readCsv et readCsvString pour prendre les infos du csv créé dans writeCSV.
	 * 
	 * @param line; correspond au nombre de ligne du fichier csv.
	 * @param filename; nom du fichier qui va être traité.
	 */
	void affichePolluant(int ligne, std::string filename); 
	
	/*!
     * @brief permet de définir l'attribut pente_ de Env à l'aide du csv contenant les pentes moyennes des fleuves de Genève. (appel readCsv pour prendre les données)
     *
     * @param filename; nom du fichier à traiter.
     */
	void setPenteCsv(std::string filename);

	/*!
     * @brief Les getters (méthodes get) permettent d'accéder aux attributs privés de cette classe en dehors de cette dernière.
     *
     * Elles sont définies const car elles ne modifient pas d'attributs de la classe.
     *
     * @return Elles retournent les attributs privé de la classe
     */
    int getLargeur() const;
	int getHauteur() const;
	int getLongueur() const;
	int getH_eau() const;
	int getH_sol() const;
	double getPente() const;
	int getPalier() const;
	Case* getTableau() const;

private :

	int largeur_; 		///< largeur de la rivière
	int hauteur_;  	    ///< hauteur de la rivière
	int longueur_;      ///< lonugueur de la rivière
	int h_sol_;			///< hauteur du sol (en cases)
	int h_eau_;			///< hauteur de l'eau (en cases) depuis tout en bas, sol compris
	double pente_;		///< pente du fond de la rivière
	int palier_;		///< nombre de case en longueur avant que la hauteur du sol augmente
	Case* tableau_;		///< tableau contenant des pointeurs sur des cases
};

#endif // Env_HPP

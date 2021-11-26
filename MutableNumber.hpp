#ifndef MUTABLENUMBER_HPP
#define MUTABLENUMBER_HPP

#pragma once

#include "JSON/JSON.hpp"

/*!
 * @class MutableNumber
 *
 * Permet de faire muter des caractéristiques des bactéries
 */
class MutableNumber {
public :

    /*!
     * @brief constructeur
     *
     * @param val la valeur du nombre mutable
     * @param proba la probabilité que le nombre mute
     * @param ecart permet une modification aléatoire du nombre
     * @param hasInf true si le nombre a un minimum, par défaut il n'en a pas
     * @param inf s'il a un minimum, c'est lui, par défaut il vaut 0.0
     * @param hasSup true si le nombre a un maximum, par défaut il n'en a pas
     * @param sup s'il a un maximum, c'est lui, par défaut il vaut 0.0
     */
    MutableNumber (double val, double proba, double ecart, bool hasInf = false,
                   double inf = 0.0, bool hasSup = false, double sup = 0.0);

    /*!
     * @brief constructeur
     *
     * @param config permet d'initialiser les attributs depuis le fichier de configuration
     */
    MutableNumber (j::Value const& config);

    /*!
     * @brief permet de modifier la valeur, en restant entre les bornes si elles existent
     *
     * @param valeur_ la nouvelle valeur que l'on veut associer au MutableNumber
     */
    void set(double valeur_);

    /*!
     * @brief permet de faire muter le MutableNumber de manière aléatoire
     */
    void mutate();

    /*!
     * @brief crée des MutableNumber de type probabilité (entre 0-1) ou de type positive (plus grand que 0)
     *
     * @param ce sont les même que pour les constructeurs
     *
     * Le static rend ces méthodes méthode de classe,
     * ce qui permet de les invoquer sans créer d'instance de cette classe
     */
    static MutableNumber probability(double valeur_, double proba, double ecart);
    static MutableNumber probability(j::Value const& config);
    static MutableNumber positive(double valeur_, double proba, double ecart, bool hasSup=false, double sup=0.0);
    static MutableNumber positive(j::Value const& config, bool hasSup=false, double sup=0.0);

    /*!
     * @brief accède à la valeur du nombre mutable
     *
     * @return la valeur du MutableNumber
     */
    double get() const;

    /*!
     * @brief constructeur par défaut
     */
    MutableNumber() = default;

private :
    double valeur;
    double proba_mutation;
    double ecart_type; ///< permet une modfication aléatoire du nombre.
    bool hasBorneInf;
    bool hasBorneSup;
    double borneInf;
    double borneSup;  ///< les valeur de borneInf et borneSup sont significative que si hasBorneInf et hasBorneSup valent true.
};

#endif // MUTABLENUMBER_HPP

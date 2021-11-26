#ifndef MUTABLECOLOR_HPP
#define MUTABLECOLOR_HPP

#pragma once

#include "MutableNumber.hpp"
#include "SFML/Graphics.hpp"

/*!
 * @class MutableColor
 *
 * Permet de faire muter la couleur des bactéries
 */
class MutableColor {
public:

    /*!
     * @brief constructeur
     *
     * @param config permet d'initialiser les attributs depuis le fichier de configuration
     */
    MutableColor (j::Value const& config);

    /*!
     * @brief fait muter la couleur
     *
     * @note elle fait muter les composantes de la couleur, qui sont des MutableNumber
     */
    void mutate();

    /*!
     * @brief accède à la couleur
     *
     * @return la couleur sous une forme reconnue par SFML
     */
    sf::Color get() const;

private:
    std::array<MutableNumber, 4> rgba;
};

#endif // MUTABLECOLOR_HPP

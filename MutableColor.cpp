#include "MutableColor.hpp"


MutableColor::MutableColor (j::Value const& config)
    : rgba {config ["r"], config ["g"], config ["b"], config ["a"]}  {}
    // initialisation du tableau array avec à la composante R un MutableNumber (config["r"],...)

void MutableColor::mutate() {
    for (auto& element : rgba) {
        element.mutate();
    }
}

sf::Color MutableColor::get() const{
    return { static_cast<sf::Uint8>(rgba[0].get() * 255),
             static_cast<sf::Uint8>(rgba[1].get() * 255),
             static_cast<sf::Uint8>(rgba[2].get() * 255),
             static_cast<sf::Uint8>(rgba[3].get() * 255)
    };
}

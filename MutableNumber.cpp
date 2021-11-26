#include "MutableNumber.hpp"
#include "Random/Random.hpp"

MutableNumber::MutableNumber (double val, double proba, double ecart, bool hasInf,
                              double inf, bool hasSup, double sup)
    : valeur(val), proba_mutation(proba), ecart_type(ecart),
      hasBorneInf(hasInf), hasBorneSup(hasSup), borneInf(inf), borneSup(sup)
{
    set(val);
}

MutableNumber::MutableNumber (j::Value const& config)
    : valeur(config ["initial"].toDouble()), proba_mutation(config ["rate"].toDouble()),
      ecart_type(config ["sigma"].toDouble()), hasBorneInf(config ["clamp min"].toBool()),
      hasBorneSup(config ["clamp max"].toBool()), borneInf(config ["min"].toDouble()),
      borneSup(config ["max"].toDouble())
{
   set(config["initial"].toDouble());
}

void MutableNumber::set(double valeur_) {

    if (hasBorneInf && (valeur_ < borneInf)) {
        valeur_ = borneInf;
    }
    if (hasBorneSup && (valeur_ > borneSup)) {
        valeur_ = borneSup;
    }
    valeur = valeur_;
}

void MutableNumber::mutate() {
    if (bernoulli(proba_mutation)) {
       double nombre_aleatoire = normal(0,ecart_type*ecart_type);
       set(valeur+nombre_aleatoire);
    }
} //ajoute un nombre aléatoire à la valeur en invoquant set qui plafonnera la valeur si nécessaire

MutableNumber MutableNumber::probability(double valeur_, double proba, double ecart) {
    MutableNumber x (valeur_, proba, ecart, true, 0.0, true, 1.0);
    return x;
}

MutableNumber MutableNumber::probability(j::Value const& config) {
    MutableNumber x (config ["initial"].toDouble(), config ["rate"].toDouble(),
                     config ["sigma"].toDouble(), true, 0.0, true, 1.0);
    return x;
}

MutableNumber MutableNumber::positive(double valeur_, double proba, double ecart, bool hasSup, double sup) {
    MutableNumber x (valeur_, proba, ecart, true, 0.0, hasSup, sup);
    return x;
}

MutableNumber MutableNumber::positive(j::Value const& config, bool hasSup, double sup) {
    MutableNumber x (config ["initial"].toDouble(), config ["rate"].toDouble(),
                     config ["sigma"].toDouble(), true, 0.0, hasSup, sup);
    return x;
}
/* Pour les quatres dernière méthode, on créer un MutableNumber avec des caractéristique différente
en appelant le constructeur avec les arguments nécessaires. */

double MutableNumber::get() const{
    return valeur;
}

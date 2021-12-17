#include <iostream>
#include "Polluant.hpp"
#include <random>
using namespace std;

Polluant::Polluant(std::string nom,double masse, int depot_x,double vitesse) 
	: nom_(nom), masse_(masse), depot_x_(depot_x), vitesse_(vitesse)
{
	setPolluant(nom);
	setCouleur();
}


void Polluant::setPolluant(std::string nom) {
	int type = 0;
	enum pollution{fer = 1, phosphate = 2, amonia = 3};
	if( nom == "fer"){
		type = 1;
	}
	switch (type) 
	{
		case fer : 
			nom_cmap_ = "Reds";
			coeff_dispersion_ = 4;
				
			break; 
		/*case phosphate : 
			nom_cmap_ = "Greens";	
			coeff_dispersion_ = 2.0;
					
			break; 
		case amonia : 
			nom_cmap_ = "copper";	
			coeff_dispersion_ = 3.0;

			break; 
		case "petrole" : 
			nom_cmap_ = "Greys"	
			coeff_dispersion_ = 1.0;
					
			break; 
		default :  //polluant inconnue facteur de dilution aux hasards
			nom_cmap_ = "binary"	
			coeff_dispersion_ = 1.0;
	*/
	}
}
/*
double Polluant::getDilution() const {
	return etat_dilution_;
} 
*/
double Polluant::getCoeffDispersion() const {
	return coeff_dispersion_;
} 

double Polluant::getMasse() const{
	return masse_;
}
void Polluant::setMasse(double nouvelle_m){
	masse_ = nouvelle_m;
}
double Polluant::getVitesse() const{
	return vitesse_;
}
void Polluant::setCouleur() {
	//remettre constexpr int si on trouve comment mettre c++11 ?
	int MIN; 
	int MAX; 
	std::random_device rd;
    std::default_random_engine eng(rd());


	if (masse_ >= 1.0) {
		MIN = 85;
		MAX = 100;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (masse_ > 0.1) {
		MIN = 70;
		MAX = 84;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (masse_ > 0.01) {
		MIN = 55;
		MAX = 69;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (masse_ > 0.001) {
		MIN = 40;
		MAX = 54;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else {
		MIN = 30;
		MAX = 39;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);	
	}
}

int Polluant::getCouleur() const{
	return couleur_;
}

int Polluant::getCaseDepart() const{
	return depot_x_;
}

std::string Polluant::getNom() const {
	return nom_;
} 

std::string Polluant::getNomCmap() const {
	return nom_cmap_;
} 

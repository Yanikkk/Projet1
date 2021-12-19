#include <iostream>
#include <random>

using namespace std;

#include "Polluant.hpp"

Polluant::Polluant(std::string nom,double masse, int depot_x,double vitesse) 
	: nom_(nom), masse_(masse), depot_x_(depot_x), vitesse_(vitesse)
{
	setPolluant(nom);
	setCouleur();
}


void Polluant::setPolluant(std::string nom) {
	int type = 0;
	enum pollution{fer = 1, phosphore = 2, ammoniac = 3};
	if(nom == "fer"){
		type = 1;
	}else if (nom == "phosphore") {
		type = 2;	
	}else if (nom == "ammoniac") {
		type = 3;
	} // ???????????????????????????????? else if inconnu ? ?????????????????????????????????????????????????
	switch (type) {
		case fer : 
			nom_cmap_ = "Reds";
			coeff_dispersion_ = 1.0;
				
			break; 
		case phosphore : 
			nom_cmap_ = "Greens";	
			coeff_dispersion_ = 0.0001;
					
			break; 
		case ammoniac : 
			nom_cmap_ = "Oranges";	
			coeff_dispersion_ = 1000.0;
			
			break; 
		default :  //polluant inconnue facteur de dilution aux hasards
			nom_cmap_ = "binary";	
			coeff_dispersion_ = 1.0;
	}
}

void Polluant::setMasse(double nouvelle_m){
	masse_ = nouvelle_m;
}

void Polluant::setCouleur() {
	//remettre constexpr int si on trouve comment mettre c++11  ?
	int MIN; 
	int MAX; 
	std::random_device rd;
    std::default_random_engine eng(rd());


	if (masse_ >= 1.0) { 
		MIN = 95;
		MAX = 100;
		std::uniform_int_distribution<int> distr(MIN, MAX); 
		couleur_ = distr(eng);
	} else if (masse_ > 0.1) { 
		MIN = 90;
		MAX = 94;
		std::uniform_int_distribution<int> distr(MIN, MAX); 
		couleur_ = distr(eng);
	} else if (masse_ > 0.01) {
		MIN = 80;
		MAX = 89;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (masse_ > 0.001) { 
		MIN = 70;
		MAX = 79;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	} else if (masse_ > 0.0001){ 
		MIN = 50;
		MAX = 69;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);	
	} else if (masse_ > 0.00001){ 
		MIN = 40;
		MAX = 49;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);	
	} else {
		MIN = 30;
		MAX = 39;
		std::uniform_int_distribution<int> distr(MIN, MAX);
		couleur_ = distr(eng);
	}
}

double Polluant::getMasse() const{
	return masse_;
}

double Polluant::getVitesse() const{
	return vitesse_;
}

double Polluant::getCoeffDispersion() const {
	return coeff_dispersion_;
} 
/*
double Polluant::getDilution() const {
	return etat_dilution_;
} 
*/
std::string Polluant::getNom() const {
	return nom_;
} 

std::string Polluant::getNomCmap() const {
	return nom_cmap_;
} 

int Polluant::getCaseDepart() const{
	return depot_x_;
}

int Polluant::getCouleur() const{
	return couleur_;
}

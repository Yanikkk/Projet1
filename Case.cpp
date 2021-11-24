#include <iostream>

#include "Case.hpp"
#include "Env.hpp"
#include "Sol.hpp"
#include "Eau.hpp"
#include "Air.hpp"

Case::Case(int x, int y, int z)
	: x_(x), y_(y), z_(z)// appel au constructeur de matiere 
	{}
void Case::setX(int x){
	x_ = x;
}
void Case::setY(int y){
	y_ = y;
}
void Case::setZ(int z){
	z_ = z;
}

void Case::setMatiere() {
	/*cout<< "h_sol_ dans setMetiere : " << env->getH_sol() << endl;
	cout  << x_ << "," << z_ << "," << y_ << endl;
	cout<< "h_eau_ dans setMetiere : " << env->getH_eau() << endl;*/
	if(z_ <= env->getH_sol()) {
		// il faut pas mettre dans le conctructeur de sol le fait qu'il prenne l'attribut env et se le donne?
		matiere_ = Sol(matiere_.getEnv2());
	
	} else if( z_ <= env->getH_eau()) {
		
		matiere_ = Eau(matiere_.getEnv2());
	
	} else {
		
		matiere_ = Air(matiere_.getEnv2());
	}
}

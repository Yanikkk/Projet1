#include <iostream>

#include "Case.hpp"
#include "Env.hpp"
#include "Sol.hpp"
#include "Eau.hpp"
#include "Air.hpp"

Case::Case(int x, int y, int z)
	: x_(x), y_(y), z_(z)// appel au constructeur de matiere 
	{
		cout<< "ok"<< endl;
		cout<<x << y << z << endl;
		}
void Case::setX(int x){
    x_ = x;
}
void Case::setY(int y){
	y_ = y;
}
void Case::setZ(int z){
	z_ = z;
}

int Case::getX() const{
	return x_;
}

int Case::getY() const{
	return y_;
}

int Case::getZ() const{
	return z_;
}

void Case::setMatiere() {
	cout<< "Case_0"<< endl;
	if(z_ <= env->getH_sol()) {
		// il faut pas mettre dans le conctructeur de sol le fait qu'il prenne l'attribut env et se le donne?
		matiere_ = Sol(matiere_.getEnv2(),"SOL");
	
	} else if( z_ <= env->getH_eau()) {
		
		matiere_ = Eau(matiere_.getEnv2(),"EAU");
	
	} else {
		
		matiere_ = Air(matiere_.getEnv2(),"AIR");
	}
}

Matiere Case::getMatiere() const{
	return matiere_;
}

#include <iostream>

#include "Case.hpp"
#include "Env.hpp"
#include "Sol.hpp"
#include "Eau.hpp"
#include "Air.hpp"

Case::Case(int x, int y, int z)
	: x_(x), y_(y), z_(z)
{
	matiere_ = nullptr; ///< initialement
}

void Case::initMatiere() {
	
	if(z_ <= env->getH_sol()) {
		matiere_ = new Sol(env,"SOL",z_);
	
	} else if( z_ <= env->getH_eau()) {
		matiere_ = new Eau(env,"EAU", z_ - env->getH_sol());
	} else {
		matiere_ = new Air(env,"AIR");
	}
}

Matiere* Case::creation(int w, int profondeur){	
	return new Eau(env,"EAU", profondeur);
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

void Case::setMatiere(Matiere* a){
	matiere_ = a;
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

Matiere* Case::getMatiere() const{
	return matiere_;
}



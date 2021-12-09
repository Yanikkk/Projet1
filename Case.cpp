#include <iostream>

#include "Case.hpp"
#include "Env.hpp"
#include "Sol.hpp"
#include "Eau.hpp"
#include "Air.hpp"

Case::Case(int x, int y, int z)
	: x_(x), y_(y), z_(z)// appel au constructeur de matiere 
	{
		//intiialement
		matiere_ = nullptr;
		//cout<< "ok"<< endl;
		//cout<<x << y << z << endl;
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
void Case::setMatiere(Matiere* a){
		matiere_ = a;
}

void Case::initMatiere() {
	std::cout <<  "a" << std::endl;
	
	
	//cout<< "case: z : "<<  z_ << endl;
	//cout<< "case: sol : "<<  env->getH_sol() << endl;
	if(z_ <= env->getH_sol()) {
		//std::cout << "sol" << std::endl;
		// il faut pas mettre dans le conctructeur de sol le fait qu'il prenne l'attribut env et se le donne?
		matiere_ = new Sol(env,"SOL",z_);
	
	} else if( z_ <= env->getH_eau()) {
		//std::cout << "eau" << std::endl;
		//std::cout << env << std::endl;
		//std::cout << matiere_.getEnv2() << std::endl;
		matiere_ = new Eau(env,"EAU", z_ - env->getH_sol());
	} else {
		//std::cout << "air" << std::endl;
		matiere_ = new Air(env,"AIR");
	}
}

Matiere* Case::getMatiere() const{
	return matiere_;
}



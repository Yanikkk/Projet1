#include <iostream>

#include "Case.hpp"
#include "Env.hpp"
#include "Sol.hpp"
#include "Eau.hpp"
#include "Air.hpp"

Case::Case(int x, int y, int z)
	: x_(x), y_(y), z_(z)// appel au constructeur de matiere 
	{
		setMatiere();
	}
	
void Case::setMatiere() {
	
	if(z_ <= env->getH_sol()) {
		
		matiere_ = Sol();
		
	} else if( z_ <= env->getH_eau()) {
		
		matiere_ = Eau();
		
	} else {
		
		matiere_ = Air();
	}
}

#include <iostream>
#include "Case.hpp"


Case::Case(int x, int y, int z)
	: x_(x), y_(y), z_(z), matiere_()  // appel au constructeur de matiere 
	{
		setMatiere();
	}
	
void Case::setMatiere(){
	if( z_ <= getH_sol()){
		matiere_ = Sol();
	}else if( z_ <= getH_eau()){
		matiere_ = Eau();
	}else{
		matiere_ = Air();
	}


}

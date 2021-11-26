#include <iostream>
#include "Env.hpp"


int main() {
	
	Env riviere(20, 30, 40); 
	// créer un objet Env avec les dimensions x, y, z passées en paramètres.
	// 40,60,200
	riviere.initTableau();	
	riviere.writeCSV();
	/*delete[] tableau_;*/ // pas oublier de supprimer le tableau -> ici ?
	return 0;
}


#include <iostream>
#include <fstream>
#include <new>

#include "Env.hpp"

Env::Env(int largeur, int hauteur, int longueur)
	:largeur_(largeur), hauteur_(hauteur), longueur_(longueur)
{
	h_sol_ = 0;
	h_eau_ = 0;
	tableau_ = new Case[hauteur*largeur*longueur];
	for(int i = 0; i< hauteur * largeur * longueur; i++){
		tableau_[i].env = this;
		tableau_[i].matiere_.setEnv2(this);
	}	
	pente_ = 0.0; 
}

int Env::getLargeur() const{
	return largeur_;
}
int Env::getHauteur() const {
	return hauteur_;
}

int Env::getH_eau() const{
	return h_eau_;
}

int Env::getH_sol() const{
	return h_sol_;
}

int Env::getPente() const{
	return pente_;
}

void Env::writeCSV(){
	std::ofstream myfile;
	myfile.open("river_Data.csv");
	myfile << "X,Y,Z,Vitesse,Matiere,Surface mouillee riviere\n";
	for(int i = 0; i< hauteur_ * largeur_ * longueur_; i++){
	myfile << tableau_[i].getX() <<","<< tableau_[i].getY() << "," << tableau_[i].getZ();
		if(tableau_[i].matiere_.getType() == "EAU"){
			myfile <<","<< tableau_[i].matiere_.getVitesse();
		}else{
			myfile <<", -";
		}// chaque case 1mx1m => surface en [m^2]
		myfile << "," << tableau_[i].matiere_.getType()<< "," << largeur_ * (h_eau_ - h_sol_)<< "\n";
	}
	//mettre string en attribut matière de si "EAU" "SOL" ou "AIR" puis dans python lire ce string et en déduire une couleur
	myfile.close();
	
}


//mettre main sûrement?
void Env::readCsv(int x, int y, string filename, vector<double*>& data, int colonne, int ligne) { // Mettre dans main ?

	ifstream myFile;
	myFile.open(filename); // mettre que si pas ouvert erreur
	string cell;
	
	
	for(int i = 0; i < x * y; i++) {
		
		if (myFile.good()) {
			getline(myFile, cell, ',');
			
			
		} else {
			break; // si c'est pas good on veut que ça finisse la boucle for
		}
		
		

		if (colonne == -1 and ligne == -1) {
			double* cell_d = new double (stod(cell));
			data.push_back(cell_d);
			

		} else if (colonne == -1) {

			if (i / x == ligne) { //vérifier
				double* cell_d = new double (stod(cell));
				data.push_back(cell_d);
			}

		} else if (ligne == -1) {

			if (i % x == colonne) { // le i != colonne pour éviter la première ligne de titre mais un peu trop spécifique à ce fichier ? est ce qu'il compte  dans le fichier csv ?
				double* cell_d = new double (stod(cell));
				data.push_back(cell_d);
			}

		} else { // plus que l'option ou ligne et colonne != -1

			if (i % x == colonne and i / x == ligne) { // corriger si on change les conditions précédentes
				
				double* cell_d = new double (stod(cell));
				data.push_back(cell_d);
				
			}
		}
	}
}

void Env::setPenteCsv(string filename) {
	int x_size = 36;
	int y_size = 23;
	vector<double*> data_pente; ///< données csv
	//colonne 9 (8) 36 x 23 (cases tableau)
	for (int i = 1; i < y_size; i++) { // la boucle permet d'appeler readCsv pour toutes les lignes sauf la première (comme ça la fonction readCsv est plus général, pas besoin d'y enlever la première ligne)
	readCsv(x_size, y_size, filename, data_pente, 8, i);
	}
	double somme = 0;
	for(unsigned int i = 0; i< data_pente.size(); i++){
			
			somme = somme + *data_pente[i];
			delete data_pente[i];
			data_pente[i] = nullptr;
	}
	data_pente.clear();
	pente_ = somme / (y_size-1);
}

void Env::initTableau(int hsol, int heau, double pente) {
	if(hsol < -1){
		hsol = -1;
	}
	if(heau < 0){
		heau = hauteur_/2 -1;
	}
	if(pente < 0){
		setPenteCsv("donnee-cours-deau.csv");
		pente = pente_;
	}
	int grandeur = hauteur_ *longueur_ * largeur_;
	int x = 0;
	int y = 0;
	int z = 0;
	int palier_pente = pente/100.0 * longueur_;
	palier_pente = 2;

	
	for(int i = 0; i < grandeur; i++){
		y = i % (largeur_);
		x = i / (largeur_*hauteur_);
		z = (i - x * largeur_ * hauteur_) / largeur_;
		tableau_[i].setX(x);
		tableau_[i].setY(y);
		tableau_[i].setZ(z);
		//cout  << x << "," << z << "," << y << endl;
		
		if( ((x % palier_pente == 0) and y == 0) and z == 0){
			hsol = hsol + 1;
			h_sol_ = hsol;
			heau = heau + 1;
			h_eau_ = heau;
		}
		tableau_[i].setMatiere();
	}
}

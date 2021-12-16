#define PY_SSIZE_T_CLEAN
#define _USE_MATH_DEFINES
#include <Python.h>
#include <iostream>
#include <math.h>
using namespace std;
#include "Env.hpp"
#include "Eau.hpp"
#include <array>
#include <vector>

Env riviere(0,0,0);
int taille = 0;
int crossSection = 0;
static PyObject * initialisation(PyObject * self, PyObject * args){
	int largeur;
	int hauteur;
	int longueur;
	if (! PyArg_ParseTuple(args, "iii", &largeur, &hauteur, &longueur)) return NULL;
	Env tampon(largeur, hauteur, longueur);
	taille = largeur * hauteur * longueur;
	crossSection = largeur * hauteur;
	riviere = tampon;
	riviere.copy(&tampon);
	riviere.initTableau();
	return Py_BuildValue("i",0);
}
void cleanFirstline(int w){
	//cout << "case enlevée: "<< w << endl;
	//cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;
	//cout <<"type de la case enelvée: " << riviere.getTableau()[w].getMatiere()->getType() << endl;
				
	delete riviere.getTableau()[w].getMatiere();
	riviere.getTableau()[w].setMatiere(nullptr);
}
int calculeProfondeur(int w){
	int zb = 0;
	for(int q = 0; q < riviere.getLargeur()*riviere.getHauteur(); q++){
		
		if(riviere.getTableau()[w -zb*riviere.getLargeur()].getMatiere() == nullptr){
			zb = zb+1;
		}else if(riviere.getTableau()[w -zb*riviere.getLargeur()].getMatiere()->getType() != "SOL"){
			zb = zb+1;
		}else if(riviere.getTableau()[w -zb*riviere.getLargeur()].getMatiere()->getType() == "SOL"){
			break;
		}
	}
	return zb;
}
double C_polluant_x(Eau* eau, Polluant* polluant, int position, double temps, int depot_x){
	int x = position / crossSection;
	int case_aval = depot_x - x;
	int surface_mouille = (riviere.getH_eau()-riviere.getH_sol())* riviere.getLargeur();
	double dispersionL =  polluant->getCoeffDispersion();
	double concentration = polluant->getMasse() / (surface_mouille*sqrt(4*M_PI*dispersionL*temps)) *exp(-pow((case_aval-polluant->getVitesse() * temps),2)/(4* dispersionL *temps));
	//on obtient sa concentration[kg/M^3]
	//sur la section mouillée
	//dans notre modèle le polluant avance tout droit ou se disperse dans les autres directions, mais il ne peut faire que un des deux pendant
	//que les cases bougent
	//retourne la concentration dans la case devant celle contenant le polluant, le reste s'est dispersé
	return concentration * surface_mouille;
}
int alea_pos(int i){
	int direction = 0;
	int y = i % (riviere.getLargeur());
	int x = i / (crossSection);
	int z = (i - x * crossSection) / riviere.getLargeur();
	int position;
	//retourne un chiffre aux hasards entre 1 et 4
	int state = 0;
	/*!
	 * Regarde où va le polluant
	 * si il bouge en z, il faut que ce soit de l'eau, sinon ça recommence
	 * si il bouge en y il faut voir si la case ne sort pas
	 * si elle sort, on retourne un int négatif
	 * */
	while (state == 0){
		direction = rand() % 4 + 1;
		switch (direction) 
		{
			case 1 : 
				//! "left"
				y++;
				if(riviere.getLargeur() < y){
				 position = -1;
				}else{ position = i++;}
				break;
			case 2 : 
				//! "right"
				y--;
				if(0 > y){
				 position = -1;
				}else{position = i--;}
				break;
			case 3 : 
				//! "up"
				z++;
				if(riviere.getTableau()[i + 1*riviere.getLargeur()].getMatiere()->getType() == "EAU"){
					state = 1;
					position = i + 1*riviere.getLargeur();
				}else{z--;}
				break;
			case 4 : 
				//! "down"	
				z--;
				if(riviere.getTableau()[i - 1*riviere.getLargeur()].getMatiere()->getType() == "EAU"){
					state = 1;
					position = i - 1*riviere.getLargeur();
				}else{z++;}
				break;
			}
	}
	return position;
}
double alea_conc(double conce){
	/*if(conce < 1e-10){
		return conce = 0.0;
	}*/
	return conce *(rand() % 50)/100;
}
void dispersion(vector<double> pollution, Polluant tampon){
	int position = 0;
	double masse = 0;
	/*!
	 * La première donnée est le point de dispersion
	 * la deuxième est le reste
	 * */
	for(int i = 0 ; i < pollution.size()-1; i += 2){
		while(pollution[i+1]>0){
			position = alea_pos(round(pollution[i]));
			/*!
			* si la case sort du tableau, on enlève une fraction
			* du polluant
			* */
			if(position = -1){
				pollution[i+1] = pollution[i+1] - alea_conc(pollution[i+1]);
			}else{
				masse = alea_conc(pollution[i+1]);
				/*!
				* sinon on transfère une partie du polluant à la position calculée
				* */
				Eau* eau_pollu =(Eau*)riviere.getTableau()[position].getMatiere();
				eau_pollu->setPolluant(tampon.getNom(),masse, position/crossSection, tampon.getVitesse());
				eau_pollu->setCouleur();
				pollution[i+1] = pollution[i+1] - masse;
			}
		}
	}
	

}

void ecoulementPlat(int w, double temps){
	/*!
	 * idée ici c'est qu'on va mettre dans un tableau "pollution"
	 * les points de dispersions (coord) et le reste(ce qu'il faut disperser autour de ce point
	 * dans un tableau, 2 à 2.
	 * */
	double conc;
	double reste;
	vector<double> pollution;
	int point_dispersion;
	Polluant tampon;
	int transvaser = 0;
	if(w/(crossSection)-1 < 0){
			cleanFirstline(w);
		}else{
			int profondeur;
			if(riviere.getTableau()[w - crossSection].getMatiere() == nullptr){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					cout << "Case avec polluant: "<< w << endl;
					cout << "Et leur concentrations: "<< eau_pollu->getPolluant()->getMasse() << endl;
					//!calcule la concentration de la case devant
					point_dispersion = w;
					conc = C_polluant_x(eau_pollu, eau_pollu->getPolluant(),w - crossSection , temps, eau_pollu->getPolluant()->getCaseDepart());
					cout << "---conc---- " << conc << endl;
					reste = eau_pollu->getPolluant()->getMasse() - conc;
					pollution.push_back(point_dispersion);
					pollution.push_back(reste);
					tampon = *eau_pollu->getPolluant() ;
					//!le reste est dispersé dans les cases d'eau environnante (en bas, en haut et gauche droite)
					transvaser = 1;
				}	
				profondeur = calculeProfondeur(w - crossSection);
				riviere.getTableau()[w - crossSection].setMatiere(riviere.getTableau()[w].getMatiere());
				Eau* eau =(Eau*)riviere.getTableau()[w-crossSection].getMatiere();
				eau->setProfondeur(profondeur);
				//cout << "case enlevée: "<< w << endl;
				//cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;
				//cout <<"type de la case enelvée: " << riviere.getTableau()[w].getMatiere()->getType() << endl;
				//la case qui a avancé contient la concentration initiale, on garde seulement la masse de polluant qui a avancé tout droit.
				if(transvaser == 1){
					/*if(conc < 1e-10){
						conc = 0;
					}*/
					eau->getPolluant()->setMasse(conc);
					eau->getPolluant()->setCouleur();
					//cout << "conc après " << eau->getPolluant()->getMasse() << endl;
					transvaser = 0;
				}
				//cout << " profondeur transmise aaaaa "<< eau2->getProfondeur() << endl;
				riviere.getTableau()[w].setMatiere(nullptr);
				//cout << "case remise : " << w - crossSection<< endl;
				//cout << "couleur de la case remise: "<<riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())].getMatiere()->getCouleur()<< endl;	
				//cout << " profondeur transmise bbbbbbbbb"<< eau3->getProfondeur() << endl;					
			if(w/(crossSection) == riviere.getLongueur()-1){
				if(riviere.getTableau()[w].getMatiere() == nullptr){
					profondeur = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,profondeur));
					//cout << "case remiseeeee : " << w << endl;
					//cout << "couleur de la case remise: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;	
					//cout << " profondeur "<< profondeur << endl;
				}
			}
		}
	}
	if(w == taille -1 ){
				//! si toutes les cases ont avancées, alors on peut disperser les polluant
				dispersion(pollution, tampon);
	}
}


void ecoulementPalier(int w){
	//int crossSection = riviere.getLargeur()*riviere.getHauteur();
		if(w/(crossSection)-1 < 0){
			cleanFirstline(w);
		}
			int profondeur;
			if(riviere.getTableau()[w - crossSection].getMatiere() == nullptr){	
				profondeur = calculeProfondeur(w - crossSection);
				riviere.getTableau()[w - crossSection].setMatiere(riviere.getTableau()[w].getMatiere());
				Eau* eau =(Eau*)riviere.getTableau()[w-crossSection].getMatiere();
				eau->setProfondeur(profondeur);
				//cout << "case enlevée: "<< w << endl;
				//cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;
				//cout <<"type de la case enelvée: " << riviere.getTableau()[w].getMatiere()->getType() << endl;
				riviere.getTableau()[w].setMatiere(nullptr);
				//cout << "case remise : " << w - crossSection<< endl;
				//cout << "couleur de la case remise: "<<riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())].getMatiere()->getCouleur()<< endl;				
			}
			if(w/(crossSection) == riviere.getLongueur()-1){

				if(riviere.getTableau()[w].getMatiere() == nullptr){
					profondeur = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,profondeur));
					//cout << "case remiseeeee : " << w << endl;
					//cout << "couleur de la case remise: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;	
					//cout << " profondeur "<< profondeur << endl;
				}
			}
			
			
}

void ecoulement_transversale(int w){
		int profondeur = 0;
		int profond_actuelle = 0;
		int profond_suivante = 0;
		int h_chgmnt_palier = 0;
	
		int position = 0;
		int xprof = 0;
		int zmax = 0;
		if(riviere.getTableau()[w].getMatiere() != nullptr ){
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				if(w/(crossSection)-1 < 0){
					cleanFirstline(w);
				}
			}
		}
		if(riviere.getTableau()[w].getMatiere() == nullptr){
			if(w/crossSection != riviere.getLongueur() -1){
				xprof = w/crossSection;
				zmax= riviere.getHauteur();
				profond_actuelle = calculeProfondeur(xprof*crossSection+ zmax*riviere.getLargeur()-1);
				profond_suivante = calculeProfondeur((xprof+1)*crossSection + zmax*riviere.getLargeur()-1);
				h_chgmnt_palier = profond_actuelle - profond_suivante;
				position = w + h_chgmnt_palier *riviere.getLargeur() + (crossSection);
				//cout << "case ajoutée : " << w << endl;
				//cout << "couleur de la case ajoutée: "<<riviere.getTableau()[position].getMatiere()->getCouleur()<< endl;	
				riviere.getTableau()[w].setMatiere(riviere.getTableau()[position].getMatiere());
				profondeur = calculeProfondeur(w);
				Eau* eau =(Eau*)riviere.getTableau()[w].getMatiere();
				eau->setProfondeur(profondeur);
				//cout << "case enlevée : " << position << endl;
				//cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;	
				riviere.getTableau()[position].setMatiere(nullptr);
			}											
		}
		if(w/(crossSection) == riviere.getLongueur()-1){

				if(riviere.getTableau()[w].getMatiere() == nullptr){
					profondeur = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,profondeur));
					//cout << "case remiseeeee : " << w << endl;
					//cout << "couleur de la case remise: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;	
					//cout << " profondeur "<< profondeur << endl;
				}
			}
}

void parPalier(int q, int w, double temps, double seuil_cumule, double vitesse) {
		int state = 0;
		int profondeur = 0;
		int lastcrossSection = 0;
		int profond_actuelle = 0;
		int profond_suivante = 0;
		int h_chgmnt_palier = 0;
	
		int position = 0;
		int xprof = 0;
		int zmax = 0;
		//int palier_state = 0;
					if(riviere.getTableau()[q].getMatiere()->getType() == "EAU"){
							if(temps >= seuil_cumule){
						/*!
						 * état 0
						 * */	
									if((q/(crossSection))-1 < 0 && state == 0){
										cleanFirstline(q);
									}
									if((q/(crossSection))-1 >=0 && state == 0){
										state = 1;
									}

						/*!
						 * état 1
						 * */	
									/*!
									 * concerne toutes les cases du palier sauf la dernière crossSection
									 * */	
									lastcrossSection = w+crossSection * riviere.getPalier();
									//jai mis les ()
									lastcrossSection = lastcrossSection / crossSection -1;
									if(q/(crossSection) < lastcrossSection  && state == 1){
										ecoulementPalier(q);
									}
									/*!
									 * concerne la dernière crossSection dans le cas où le palier ne vaut pas 1
									 * */
									if(q/(crossSection) == lastcrossSection && state == 1){
										if(riviere.getTableau()[q].getMatiere() !=nullptr){
											riviere.getTableau()[q- (crossSection)].setMatiere(riviere.getTableau()[q].getMatiere());
											profondeur = calculeProfondeur(q-(crossSection));
											//cout << "case remise : " << q-crossSection << endl;
											//cout << "couleur de la case remise: "<<riviere.getTableau()[q-crossSection].getMatiere()->getCouleur()<< endl;	
											//cout << " profondeur calculée "<< profondeur << endl;
											Eau* eau =(Eau*)riviere.getTableau()[q-crossSection].getMatiere();
											eau->setProfondeur(profondeur);
											cout << "case enlevée: "<< q << endl;
											//cout << "couleur de la case enlevée: "<<riviere.getTableau()[q].getMatiere()->getCouleur()<< endl;
											//cout <<"type de la case enelvée: " << riviere.getTableau()[q].getMatiere()->getType() << endl;
											riviere.getTableau()[q].setMatiere(nullptr);
											}
												if(riviere.getTableau()[q].getMatiere() == nullptr){
												if(q/crossSection == riviere.getLongueur() -1){
														ecoulementPalier(q);
												}
												if(q/crossSection != riviere.getLongueur() -1){
												xprof = q/crossSection;
												zmax= riviere.getHauteur();
												profond_actuelle = calculeProfondeur(xprof*crossSection+ zmax*riviere.getLargeur()-1);
												profond_suivante = calculeProfondeur((xprof+1)*crossSection + zmax*riviere.getLargeur()-1);
												h_chgmnt_palier = profond_actuelle - profond_suivante;
												position = q + h_chgmnt_palier *riviere.getLargeur() + (crossSection);
												//cout << "case ajoutée : " << q << endl;
												//cout << "couleur de la case ajoutée: "<<riviere.getTableau()[position].getMatiere()->getCouleur()<< endl;	
												riviere.getTableau()[q].setMatiere(riviere.getTableau()[position].getMatiere());
												profondeur = calculeProfondeur(q);
												Eau* eau =(Eau*)riviere.getTableau()[q].getMatiere();
												eau->setProfondeur(profondeur);
												//cout << "case enlevée : " << position << endl;
												//cout << "couleur de la case enlevée: "<<riviere.getTableau()[q].getMatiere()->getCouleur()<< endl;	
												riviere.getTableau()[position].setMatiere(nullptr);
												}											
											}
										}
									}

								}
}
void simulation_non_conforme(int w){
	int x = w/crossSection;
	int z = (w -x * riviere.getLargeur() * riviere.getHauteur()) / riviere.getLargeur();
	int hauteur_eau = riviere.getH_eau()-riviere.getH_sol();
	Eau* eau =(Eau*)riviere.getTableau()[w].getMatiere();
	if(z - eau->getProfondeur() + hauteur_eau > riviere.getHauteur()){
		cout << "\n" << endl;
		cout << "--------------------------------------------------------------"<< endl;
		cout << "Erreur due a une taille non-conforme de la simulation" << endl;
		cout << "Veuillez tenir compte du fait que l'eau ne doit pas deborder" << endl;
		cout << "Pour rappel voici les valeurs actuelles: \n" << endl;
		cout << "Le palier :" << riviere.getPalier() << endl;
		cout << "La largeur :" << riviere.getLargeur() << endl;
		cout << "La hauteur :" << riviere.getHauteur() << endl;
		cout << "La longueur :" << riviere.getLongueur() << endl;
		cout << "\nLa simulation est non conforme car en (x,z) = (" << x << "," << z << "), " << endl;
		cout << "on a une hauteur d'eau de :" << z - eau->getProfondeur() + hauteur_eau  << endl;
		cout << "pour une hauteur totale de tableau de : " << riviere.getHauteur() << endl;
		
		cout << "\n\nVeuillez reessayer avec des valeurs conformes" << endl;
		cout <<"(Ps: par exemple : larg = 20, haut = 30, long = 40)" << endl;
		cout << "--------------------------------------------------------------"<< endl;
		exit(0);
	}
}
void erreur_de_palier(){
		cout << "\n" << endl;
		cout << "--------------------------------------------------------------"<< endl;
		cout << "Erreur due a un palier non conforme" << endl;
		cout << "Veuillez tenir compte du fait que l'eau doit aller jusqu'au bout de la simulation" << endl;
		cout << "Pour rappel voici les valeurs actuelles: \n" << endl;
		cout << "Le palier :" << riviere.getPalier() << endl;
		cout << "La largeur :" << riviere.getLargeur() << endl;
		cout << "La hauteur :" << riviere.getHauteur() << endl;
		cout << "La longueur :" << riviere.getLongueur() << endl;
		cout << "\nLa simulation est non conforme car en (x,z) = (" << riviere.getLongueur() -1 << "," << riviere.getHauteur() -1 << "), " << endl;
		cout << "on a une case de sol." << endl;;
		
		cout << "\n\nVeuillez reessayer avec des valeurs conformes" << endl;
		cout <<"(Ps: par exemple : larg = 20, haut = 30, long = 40 et palier = 10)" << endl;
		cout << "--------------------------------------------------------------"<< endl;
		exit(0);
}
void detection_erreur(){
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
			simulation_non_conforme(w);
		}
	}
	if(riviere.getTableau()[taille-1].getMatiere()->getType() == "SOL"){
		erreur_de_palier();
	}

}

double seuil_cumule = 0.0;
static PyObject * ecoulement(PyObject * self, PyObject * args){
	/*!
	 * On détecte une possible erreur de dimension 
	 * du tableau ou du palier choisit.
	 */	
	detection_erreur();
	int case_pollue = 0;
	/*!
	 * Cette boucle va détecter le point de dépot du polluant (x,y,z).
	 * Sachant qu'il ne peut que être déposer sur le dessus de l'eau en
	 * 
	 */
	double temps;
	double vitesse = 0;
	if (! PyArg_ParseTuple(args, "d", &temps)) return NULL;
	/*!
	 * cas si la rivière est plus petite que un palier
	 * donc si elle est plate
	 * */
	if(riviere.getPalier() >= taille/crossSection){
		for(int w = 0; w < taille; w++){
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				vitesse = riviere.getTableau()[w].getMatiere()->getVitesse();
				if(seuil_cumule == 0.0){
					seuil_cumule = seuil_cumule + 1/vitesse;
				}
				if(temps >= seuil_cumule){
					ecoulementPlat(w, temps);
				}
			}
		}
		if(temps >= seuil_cumule){
			seuil_cumule = seuil_cumule + 1/vitesse;
		}
	}else if(riviere.getLongueur() % riviere.getPalier() == 0 && riviere.getPalier() != 1){ 
	/*!
     * @biref
     * si la rivière à une pente et si le palier sépare la rivière en partie égale sauf cas palier = 1
     * état 0 => on traite les cases en première ligne
     * état 1 => on traite les cases en non situation de débordement
     * état 2 => se met en place quand il y a un état de dépacement
     * */
			for(int w = 0; w <= taille - crossSection * riviere.getPalier(); w += crossSection * riviere.getPalier()){
				for(int q = w; q < w+crossSection * riviere.getPalier(); q++){
					
						if(riviere.getTableau()[q].getMatiere() != nullptr && riviere.getTableau()[q].getMatiere()->getType() == "EAU"){
							vitesse = riviere.getTableau()[q].getMatiere()->getVitesse();
									if(seuil_cumule == 0){
										seuil_cumule =  1/vitesse;
									}
						}else{ continue;}
							parPalier(q,w, temps, seuil_cumule, vitesse);
					}
				}
			if(temps >= seuil_cumule){
			seuil_cumule = seuil_cumule + 1/vitesse;
			}	
	}else if(riviere.getPalier() == 1){
	/*!
     * @biref
     * cas palier = 1;
     * */
		for(int w = 0; w < taille; w++ ){
					ecoulement_transversale(w);
		}
	}else{ 
			/*!
			* @biref
			* si la rivière à une pente et si le palier ne sépare pas la rivière en partie égale
			* */
			int caseRestante = taille %(crossSection * (riviere.getPalier()));
			for(int w = 0; w <= taille - crossSection * riviere.getPalier(); w += crossSection * riviere.getPalier()){
				for(int q = w; q < w+crossSection * riviere.getPalier(); q++){
						if(riviere.getTableau()[q].getMatiere() != nullptr && riviere.getTableau()[q].getMatiere()->getType() == "EAU"){
						vitesse = riviere.getTableau()[q].getMatiere()->getVitesse();
									if(seuil_cumule == 0){
										seuil_cumule =  1/vitesse;
									}
						}else{ continue;}
						parPalier(q,w, temps, seuil_cumule, vitesse);
				}
			}
				for(int w = taille - caseRestante + crossSection; w < taille; w++){
					if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
						vitesse = riviere.getTableau()[w].getMatiere()->getVitesse();
						if(temps >= seuil_cumule){
							ecoulementPlat(w, temps);
						}
					}
				}
				if(caseRestante == crossSection){
					for(int w = taille- crossSection; w < taille; w++){
						if(riviere.getTableau()[w].getMatiere() == nullptr){
							if(temps >= seuil_cumule){
								if(riviere.getTableau()[w].getMatiere() == nullptr){
										riviere.getTableau()[w].setMatiere(riviere.creation(w, calculeProfondeur(w)));
								}
							}
						}
					}
				
					
				}
				if(temps >= seuil_cumule){
					seuil_cumule = seuil_cumule + 1/vitesse;			
				}
			
		}
	return Py_BuildValue("i",0);
}

static PyObject * pollution(PyObject * self, PyObject * args){
	cout << "0" << endl;
	int pollution_state;
	int w = 0;
	if (! PyArg_ParseTuple(args, "i", &pollution_state)) return NULL;
	int z_maxEau = 0;
	int xmax = riviere.getLongueur()-1;
	//cas du Fer par exemple
	if(pollution_state == 1){
		for(int w = taille -1; w >= taille - (riviere.getLargeur()*riviere.getLongueur()); w--){
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				z_maxEau = (w -xmax*riviere.getLargeur() * riviere.getHauteur())/riviere.getLargeur();
				break;
			}
		}
		//génère un nombre sur la dernière ligne d'eau de la dernière crossSection de la simulation
		w = rand() % riviere.getLargeur() + taille - (riviere.getHauteur()- z_maxEau) * riviere.getLargeur(); 
		cout << "ad "<< w << endl;
		Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
		eau_pollu->setPolluant("fer", 10.0, riviere.getLongueur() -1, eau_pollu->getVitesse());
	}
	
	
	
return Py_BuildValue("i",0);
}

static PyObject * coord_X(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* matiere;
	if (! PyArg_ParseTuple(args, "s", &matiere)) return NULL;
	if(matiere == "EAU_POLLUE"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
				}	
			}
		}
	}else{
		for(int w = 0; w < taille; w++){
			if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
				if(matiere == "EAU"){
					Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
					if(eau_pollu->getPolluant() == nullptr){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
					}
				}else{
					if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
					}
				}
			}
		}
	}
	return data_animation;
}
static PyObject * coord_Y(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* matiere;
	if (! PyArg_ParseTuple(args, "s", &matiere)) return NULL;
	if(matiere == "EAU_POLLUE"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
				}	
			}
		}
	}else{
		for(int w = 0; w < taille; w++){
			if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
				if(matiere == "EAU"){
					Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
					if(eau_pollu->getPolluant() == nullptr){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
					}
				}else{
					if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
					}
				}
			}
		}
	}
	return data_animation;
}
static PyObject * coord_Z(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* matiere;
	if (! PyArg_ParseTuple(args, "s", &matiere)) return NULL;
	if(matiere == "EAU_POLLUE"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
				}	
			}
		}
	}else{
		for(int w = 0; w < taille; w++){
			if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
				if(matiere == "EAU"){
					Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
					if(eau_pollu->getPolluant() == nullptr){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
					}
				}else{
					if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
					}
				}
			}
		}
	}
	return data_animation;
}
static PyObject * getCouleur_sol(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "SOL"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getMatiere()->getCouleur()));
		}
	}
	return data_animation;
}
static PyObject * getCouleur_air(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "AIR"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getMatiere()->getCouleur()));
		}
	}
	return data_animation;
}
static PyObject * getCouleur_eau(PyObject * self, PyObject * args){
	char* matiere;
	if (! PyArg_ParseTuple(args, "s", &matiere)) return NULL;
	PyObject * data_animation = PyList_New(0);
	if(matiere == "EAU_POLLUE"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					PyList_Append(data_animation, Py_BuildValue("i",eau_pollu->getPolluant()->getCouleur()));
				}	
			}
		}	
	}
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() == nullptr){
					PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getMatiere()->getCouleur()));
				}
		}
	}
	return data_animation;
}
static PyObject * Cmap(PyObject * self, PyObject * args){
	char* polluant;
	if (! PyArg_ParseTuple(args, "s", &polluant)) return NULL;
	PyObject * data_animation = PyList_New(0);
	if(polluant == "fer"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					if(eau_pollu->getPolluant()->getNom() == "fer"){
						return Py_BuildValue("s",eau_pollu->getPolluant()->getNom().c_str());
					}
				}	
			}
		}	
	}
	return  Py_BuildValue("i",0);
}

//iii = int int intn
//liste python marche mais gourmand
//autre possibilité renvoyer un numpy

static PyMethodDef methods[] = {
	{"initialisation", initialisation, METH_VARARGS, "Initialisation de environnement riviere."},
	{"ecoulement", ecoulement, METH_VARARGS, "Fait avancer les cases EAU"},
	{"pollution", pollution, METH_VARARGS,"Propage les polluants dans l'eau"},
	{"coord_X", coord_X, METH_VARARGS, "Les coordonnee x de matieres"},
	{"coord_Y", coord_Y, METH_VARARGS, "Les coordonnee y de matieres"},
	{"coord_Z", coord_Z, METH_VARARGS, "Les coordonnee z de matieres"},
	{"getCouleur_sol", getCouleur_sol, METH_VARARGS, "Les couleurs des cases de sol"},
	{"getCouleur_air", getCouleur_air, METH_VARARGS, "Les couleurs des cases d'air"},
	{"getCouleur_eau", getCouleur_eau, METH_VARARGS, "Les couleurs des cases d'eau"},
	{"Cmap", Cmap, METH_VARARGS, "Les couleurs de polluant"},
	//nom en python, nom en C, comment gérer les arguments(voir internet), description de la fonction(no interest
	{NULL, NULL, 0, NULL}
	};

static struct PyModuleDef moduleDefinition = { //struct de config de module
    PyModuleDef_HEAD_INIT,
    "Noyau", //nom module
    "Simulation d une riviere.", //même que en haut
    -1, //point tech.
    methods
	};
PyMODINIT_FUNC
PyInit_Noyau(void) { //main de mon module , accède avec le import
	// Module avec les méthodes
	PyObject * module = PyModule_Create(&moduleDefinition); //donc avec le import appelle cette fonction

    return module;
}

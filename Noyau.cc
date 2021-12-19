#define PY_SSIZE_T_CLEAN
#define _USE_MATH_DEFINES
#include <Python.h>
#include <iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "Env.hpp"
#include "Eau.hpp"
#include <array>
#include <vector>


//! Quelques variables globales
Env riviere(0,0,0);
int taille = 0;
int crossSection = 0;
vector<double> pollution_tab;


static PyObject * initialisation(PyObject * self, PyObject * args){
	srand(time(NULL));
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
	int case_aval = depot_x -  riviere.getTableau()[position].getX();;
	int surface_mouille = (riviere.getH_eau()-riviere.getH_sol())* riviere.getLargeur();
	double dispersionL =  polluant->getCoeffDispersion();
	if(polluant->getMasse() <=0.0){
		return 0.0;
	}
	double concentration = polluant->getMasse() / (surface_mouille*sqrt(4*M_PI*dispersionL*temps)) *exp(-pow((case_aval-polluant->getVitesse() * temps),2)/(4* dispersionL *temps));
	return concentration * surface_mouille;
}

int alea_bis(int i){
	int x = riviere.getTableau()[i].getX();
	int y = riviere.getTableau()[i].getY();
	int z = riviere.getTableau()[i].getZ();

	int state = 0;
	int direction = 0;
	while (state == 0){
		direction = rand() % 7 + 1;
		
		switch (direction) 
		{
			case 1 : 
				//! "left front"
				x--;
				y++;
				if(riviere.getLargeur()-1 < y || x < 0){
				  return -2;
				}
				if (riviere.getTableau()[i + 1 - 1*crossSection].getMatiere()->getType() == "EAU"){
					return i+1 - crossSection;	
				}	
				y--;
				x++;			
				break;
			case 2 : 
				//! "right front"
				x--;
				y--;
				if(0 > y || x < 0){
				 return -2;
				}
				if(riviere.getTableau()[i -1 - 1*crossSection].getMatiere()->getType() == "EAU"){
						return i-1 -crossSection;
				}
				y++;
				x++;
				break;
			case 3 : 
				//! "left front down"
				x--;
				z--;
				y++;
				if(riviere.getLargeur()-1 < y || x < 0){
					return -2;
				}
				if(z >0){
					if (riviere.getTableau()[i + 1 -1 * riviere.getLargeur() - crossSection].getMatiere()->getType() == "EAU"){
						return i + 1- riviere.getLargeur() -crossSection;
					}
				}		
				x++;
				z++;
				y--;
				break;
			case 4 : 
				//! "right front down"	
				x--;
				z--;
				y--;
				if(0 > y || x < 0){
					return -2;
				}
				if( z > 0){
					if(riviere.getTableau()[i -1 - 1*riviere.getLargeur() -crossSection].getMatiere()->getType() == "EAU"){
						return i -1 - riviere.getLargeur() - crossSection;
					}
				}
				x++;
				z++;
				y++;			
				break;
			case 5:
				//! "left front up"
				x--;
				z++;
				y++;
				if(riviere.getLargeur()-1 < y || x < 0){
					return -2;
				}
				if(z <= riviere.getHauteur()-1){ 
					if (riviere.getTableau()[i + 1 + 1 * riviere.getLargeur() - crossSection].getMatiere()->getType() == "EAU"){
						return i + + riviere.getLargeur() -crossSection;
					}
				}		
				x++;
				z--;
				y--;
				break;
			case 6:
			//! "right front up"
				x--;
				z++;
				y--;
				if(0 > y || x < 0){
					return -2;
				}
				if(z <= riviere.getHauteur()-1){
					if(riviere.getTableau()[i -1 + 1*riviere.getLargeur() -crossSection].getMatiere()->getType() == "EAU"){
						return i -1 + riviere.getLargeur() - crossSection;
					}
				}
				x++;
				z--;
				y++;
				break;
			case 7:
			//! "front"
				x--;
				if(x < 0){
					return -2;
				}
				if(riviere.getTableau()[i - crossSection].getMatiere()->getType() == "EAU"){
					return i - crossSection;
				}
				x++;
				break;	
		}
	}
	cout << "-----------------" << endl;
	cout << "Pas de direction " << endl;
	cout << "Pour le polluant ."<< endl;
	cout << "-----------------" << endl;
	exit(0);
	return 0;
}

int alea_pos(int i, int transversale){
	int direction = 0;
	int y = riviere.getTableau()[i].getY();
	int z = riviere.getTableau()[i].getZ();
	int compteur = 1;
	int state = 0;
	/*!
	 * Regarde où va le polluant.
	 * Il doit finir dans de l'eau.
	 * Si il sort du tableau sur les côtés,
	 * il sort de la simulation et ets donc effacé.
	 * */
	while (state == 0){
		direction = rand() % 4 + 1;

		if(transversale == 1){
			compteur--;
			if(compteur == 0){
					state = 0;
			}
		}
		switch (direction) 
		{
			case 1 : 
				//! "left"
				y++;
				if(riviere.getLargeur()-1 < y){
				  return -2;
				}else{
					return i+1;}
				break;
			case 2 : 
				//! "right"
				y--;
				if(0 > y){
				 return -2;
				}else{
					return i-1;}
				break;
			case 3 : 
				//! "up"
				z++;
				if(z <= riviere.getHauteur()-1){
					if(riviere.getTableau()[i + 1*riviere.getLargeur()].getMatiere()->getType() == "EAU"){
						return i + 1*riviere.getLargeur();
					}else{
						z--;
					}
				}
					break;
			case 4 : 
				//! "down"	
				z--;
				if(riviere.getTableau()[i - 1*riviere.getLargeur()].getMatiere()->getType() == "EAU"){
					return i - 1*riviere.getLargeur();
				}else{z++;}
				break;
			}
	}
	cout << "-----------------" << endl;
	cout << "Pas de direction " << endl;
	cout << "Pour le polluant ."<< endl;
	cout << "-----------------" << endl;
	exit(0);
	return 0;
}

double alea_conc(double/* * */ conce){
	if(conce <= 0.0){
		return 0.0;
	}
	return conce *(rand() % 40)/100 + conce * 1/2;
}

int string_to_code(std::string nom_pollu){
	if(nom_pollu == "fer"){
		return 1;
	}
	if(nom_pollu == "phosphore"){
		return 2;
	}
	if(nom_pollu == "ammoniac"){
		return 3;
	}
	return -1;
}

string code_to_string(int numero_pollu){
	if(numero_pollu == 1){
		return "fer";
	}
	if(numero_pollu == 2){
		return "phosphore";
	}
	if(numero_pollu == 3){
		return "ammoniac";
	}
	
	return "Inconnu";
}

void verifie_disp(vector<double> bis);

void dispersion(int type){
	int position = 0;
	double masse = 0;
	/*!
	 * La première donnée est le point de dispersion
	 * la deuxième est le reste
	 * la troisième est le nom du polluant
	 * soit:	1 => fer
	 * 				2=> phosphore
	 * 					3=> ammoniac
	 * la quatrième est sa vitesse
	 * */
	for(int i = 0 ; i < pollution_tab.size()-1; i += 4){
		while(pollution_tab[i+1] >= 1e-5){
			if(type == 0){
				if( 1 == (rand() %2 +1)){
					position = alea_pos(round(pollution_tab[i]),0);
				}else{
					position = alea_bis(round(pollution_tab[i]));
					}
			}
			/*!
			 * écoulement transversale
			 * */	
			if(type == 1){
					if( 1 == (rand() %2 +1)){
							position = alea_pos(round(pollution_tab[i]),1);
					}else{
						position = alea_bis(round(pollution_tab[i]));
						}
			}
			/*!
			* si la case sort du tableau, on enlève une fraction
			* du polluant
			* */
			masse = alea_conc(pollution_tab[i+1]);
	
			
			if(position == -2){
					pollution_tab[i+1] = pollution_tab[i+1] - masse;
			}else{
				Eau* eau_pollu =(Eau*)riviere.getTableau()[position].getMatiere();
				 if(eau_pollu->getPolluant() != nullptr){
							eau_pollu->getPolluant()->setMasse(masse + eau_pollu->getPolluant()->getMasse());
							pollution_tab[i+1] = pollution_tab[i+1] - masse;		
							eau_pollu->setCouleur();	
				}else{
						eau_pollu->setPolluant(code_to_string(round(pollution_tab[i+2])),masse, position/crossSection, pollution_tab[i+3]);
						eau_pollu->setCouleur();
						pollution_tab[i+1] = pollution_tab[i+1] - masse;
				}
			}
		}
	}		
}

int last_eau(){
	for(int i = taille -1; i >= taille - crossSection; i--){
		if(riviere.getTableau()[i].getMatiere() == nullptr){
				return i;
		}else if(riviere.getTableau()[i].getMatiere()->getType() == "EAU"){
				return i;
		}
	}
	return -1;
}

void ecoulementPlat(int w, double temps){
	/*!
	 * idée ici c'est qu'on va mettre dans un tableau "pollution_tab" (variable globale)
	 * les points de dispersions (coord), le reste(ce qu'il faut disperser autour de ce point),
	 * le nom du polluant et sa vitesse
	 * */
	double conc;
	double reste;
	double point_dispersion;
	int transvaser = 0;
	
	if(w/(crossSection)-1 < 0){
			cleanFirstline(w);
		}else{
			int profondeur;
			if(riviere.getTableau()[w - crossSection].getMatiere() == nullptr){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					point_dispersion = w;
					conc = C_polluant_x(eau_pollu, eau_pollu->getPolluant(),w - crossSection , temps, eau_pollu->getPolluant()->getCaseDepart());
					if(conc <= 0.0){
						conc = 0.0;
						reste =0.0;
					}
					reste = eau_pollu->getPolluant()->getMasse() - conc;
					if(reste >= 1e-6){
						pollution_tab.push_back(point_dispersion);
						pollution_tab.push_back(reste);
						pollution_tab.push_back(string_to_code( eau_pollu->getPolluant()->getNom()));
						pollution_tab.push_back(eau_pollu->getPolluant()->getVitesse());
					}
					transvaser = 1;
					//!le reste est dispersé dans les cases d'eau environnante (en bas, en haut et gauche droite)
				}
				profondeur = calculeProfondeur(w - crossSection);
				riviere.getTableau()[w - crossSection].setMatiere(riviere.getTableau()[w].getMatiere());
				Eau* eau =(Eau*)riviere.getTableau()[w-crossSection].getMatiere();
				eau->setProfondeur(profondeur);
				if(transvaser == 1){
					if(conc < 1e-6){
						conc = 0;
						delete eau->getPolluant();
						eau->setPolluant("nullptr");
					}else{
						if(eau->getPolluant() != nullptr){
							eau->getPolluant()->setMasse(conc);
							eau->getPolluant()->setCouleur();;
							transvaser = 0;
						}
					}
				}
				riviere.getTableau()[w].setMatiere(nullptr);						
			if(w/(crossSection) == riviere.getLongueur()-1){
				if(riviere.getTableau()[w].getMatiere() == nullptr){
					profondeur = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,profondeur));
				}
			}
		}
	}
	if(last_eau() == -1){
		cout << "----------------------" << endl;
		cout << "Erreur, il n'y a pas de" << endl;
		cout << "case eau ." << endl;
		cout << "----------------------" << endl;
		exit(0);
	}
	if(pollution_tab.size() != 0){
		if(w == last_eau() ){
		dispersion(0);
		}
	}
	
}

void ecoulementPalier(int w, double temps){
	double conc;
	double reste;
	double point_dispersion;
	int transvaser = 0;

			int profondeur;
			if(riviere.getTableau()[w - crossSection].getMatiere() == nullptr){	
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					point_dispersion = w;
					conc = C_polluant_x(eau_pollu, eau_pollu->getPolluant(),w - crossSection , temps, eau_pollu->getPolluant()->getCaseDepart());
					if(conc <= 0.0){
						conc = 0.0;
						reste =0.0;
					}
					reste = eau_pollu->getPolluant()->getMasse() - conc;
					if(reste >= 1e-6){
						pollution_tab.push_back(point_dispersion);
						pollution_tab.push_back(reste);
						pollution_tab.push_back(string_to_code( eau_pollu->getPolluant()->getNom()));
						pollution_tab.push_back(eau_pollu->getPolluant()->getVitesse());
					}
					transvaser = 1;
					//!le reste est dispersé dans les cases d'eau environnante (en bas, en haut et gauche droite)
				}
				profondeur = calculeProfondeur(w - crossSection);
				riviere.getTableau()[w - crossSection].setMatiere(riviere.getTableau()[w].getMatiere());
				Eau* eau =(Eau*)riviere.getTableau()[w-crossSection].getMatiere();
				eau->setProfondeur(profondeur);
				if(transvaser == 1){
					if(conc < 1e-6){
						conc = 0;
						delete eau->getPolluant();
						eau->setPolluant("nullptr");
					}else{
						if(eau->getPolluant() != nullptr){
							eau->getPolluant()->setMasse(conc);
							eau->getPolluant()->setCouleur();;
							transvaser = 0;
						}
					}
				}
				riviere.getTableau()[w].setMatiere(nullptr);
			}
			if(w/(crossSection) == riviere.getLongueur()-1){

				if(riviere.getTableau()[w].getMatiere() == nullptr){
					profondeur = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,profondeur));
				}
			}
			
}

void ecoulement_transversale(int w, double temps){
	double conc;
	double  reste;
	double  point_dispersion;
	int transvaser = 0;
	
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
				xprof = riviere.getTableau()[w].getX();
				zmax= riviere.getHauteur();
				profond_actuelle = calculeProfondeur(xprof*crossSection+ zmax*riviere.getLargeur()-1);
				profond_suivante = calculeProfondeur((xprof+1)*crossSection + zmax*riviere.getLargeur()-1);
				h_chgmnt_palier = profond_actuelle - profond_suivante;
				position = w + h_chgmnt_palier *riviere.getLargeur() + (crossSection);
				Eau* eau_pollu =(Eau*)riviere.getTableau()[position].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					point_dispersion = position;
					conc = C_polluant_x(eau_pollu, eau_pollu->getPolluant(),w - crossSection , temps, eau_pollu->getPolluant()->getCaseDepart());
					if(conc <= 0.0){
						conc = 0.0;
						reste =0.0;
					}
					reste = eau_pollu->getPolluant()->getMasse() - conc;
					if(reste >= 1e-6){
						pollution_tab.push_back(point_dispersion);
						pollution_tab.push_back(reste);
						pollution_tab.push_back(string_to_code( eau_pollu->getPolluant()->getNom()));
						pollution_tab.push_back(eau_pollu->getPolluant()->getVitesse());
					}
					transvaser = 1;
				}
				riviere.getTableau()[w].setMatiere(riviere.getTableau()[position].getMatiere());
				profondeur = calculeProfondeur(w);
				Eau* eau =(Eau*)riviere.getTableau()[w].getMatiere();
				eau->setProfondeur(profondeur);
				if(transvaser == 1){
					if(conc < 1e-6){
						conc = 0;
						delete eau->getPolluant();
						eau->setPolluant("nullptr");
					}else{
						if(eau->getPolluant() != nullptr){
							eau->getPolluant()->setMasse(conc);
							eau->getPolluant()->setCouleur();;
							transvaser = 0;
						}
					}
				}
				riviere.getTableau()[position].setMatiere(nullptr);
			}									
		}
		if(w/(crossSection) == riviere.getLongueur()-1){

				if(riviere.getTableau()[w].getMatiere() == nullptr){
					profondeur = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,profondeur));
				}
			}
	if(last_eau() == -1){
		cout << "----------------------" << endl;
		cout << "Erreur, il n'y a pas de" << endl;
		cout << "case eau ." << endl;
		cout << "----------------------" << endl;
		exit(0);
	}
	if(pollution_tab.size() != 0){
		if(w == last_eau() ){
		dispersion(1);
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
		
		double conc;
		double  reste;
		double  point_dispersion;
		int transvaser = 0;
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
									lastcrossSection = (lastcrossSection / crossSection) -1;
									if(q/(crossSection) < lastcrossSection  && state == 1){
										ecoulementPalier(q, temps);
									}
									/*!
									 * concerne la dernière crossSection du palier
									 * */
									if(q/(crossSection) == lastcrossSection && state == 1){
										if(riviere.getTableau()[q].getMatiere() !=nullptr){
											Eau* eau_pollu =(Eau*)riviere.getTableau()[q].getMatiere();	
											if(eau_pollu->getPolluant() != nullptr){
												point_dispersion = q;
												conc = C_polluant_x(eau_pollu, eau_pollu->getPolluant(),q - crossSection , temps, eau_pollu->getPolluant()->getCaseDepart());
											if(conc <= 0.0){
												conc = 0.0;
												reste =0.0;
											}
												reste = eau_pollu->getPolluant()->getMasse() - conc;
											if(reste >= 1e-6){
												pollution_tab.push_back(point_dispersion);
												pollution_tab.push_back(reste);
												pollution_tab.push_back(string_to_code( eau_pollu->getPolluant()->getNom()));
												pollution_tab.push_back(eau_pollu->getPolluant()->getVitesse());
											}
												transvaser = 1;
										}
										riviere.getTableau()[q- (crossSection)].setMatiere(riviere.getTableau()[q].getMatiere());
										profondeur = calculeProfondeur(q-(crossSection));	
										Eau* eau =(Eau*)riviere.getTableau()[q-crossSection].getMatiere();
										eau->setProfondeur(profondeur);
											if(transvaser == 1){
												if(conc < 1e-6){
													conc = 0;
													delete eau->getPolluant();
													eau->setPolluant("nullptr");
												}else{
													if(eau->getPolluant() != nullptr){
														eau->getPolluant()->setMasse(conc);
														eau->getPolluant()->setCouleur();;
														transvaser = 0;
													}
												}
											}
											riviere.getTableau()[q].setMatiere(nullptr);
											}
												if(riviere.getTableau()[q].getMatiere() == nullptr){
												if(q/crossSection == riviere.getLongueur() -1){
													ecoulementPalier(q,temps);
												}
												if(q/crossSection != riviere.getLongueur() -1){
												xprof = q/crossSection;
												zmax= riviere.getHauteur();
												profond_actuelle = calculeProfondeur(xprof*crossSection+ zmax*riviere.getLargeur()-1);
												profond_suivante = calculeProfondeur((xprof+1)*crossSection + zmax*riviere.getLargeur()-1);
												h_chgmnt_palier = profond_actuelle - profond_suivante;
												position = q + h_chgmnt_palier *riviere.getLargeur() + (crossSection);
												riviere.getTableau()[q].setMatiere(riviere.getTableau()[position].getMatiere());
												Eau* eau_pollu =(Eau*)riviere.getTableau()[q].getMatiere();
												if(eau_pollu->getPolluant() != nullptr){
													point_dispersion = q;
													conc = C_polluant_x(eau_pollu, eau_pollu->getPolluant(),q - crossSection , temps, eau_pollu->getPolluant()->getCaseDepart());
													if(conc <= 0.0){
														conc = 0.0;
														reste =0.0;
													}
														reste = eau_pollu->getPolluant()->getMasse() - conc;
													if(reste >= 1e-6){
														pollution_tab.push_back(point_dispersion);
														pollution_tab.push_back(reste);
														pollution_tab.push_back(string_to_code( eau_pollu->getPolluant()->getNom()));
														pollution_tab.push_back(eau_pollu->getPolluant()->getVitesse());
													}
													transvaser = 1;
												}	
												profondeur = calculeProfondeur(q);
												Eau* eau =(Eau*)riviere.getTableau()[q].getMatiere();
												eau->setProfondeur(profondeur);
												if(transvaser == 1){
													if(conc < 1e-6){
														conc = 0;
														delete eau->getPolluant();
														eau->setPolluant("nullptr");
													}else{
														if(eau->getPolluant() != nullptr){
															eau->getPolluant()->setMasse(conc);
															eau->getPolluant()->setCouleur();;
															transvaser = 0;
														}
													}
												}	
												riviere.getTableau()[position].setMatiere(nullptr);
												}											
											}
										}
									}

								}
	if(last_eau() == -1){
		cout << "----------------------" << endl;
		cout << "Erreur, il n'y a pas de" << endl;
		cout << "case eau ." << endl;
		cout << "----------------------" << endl;
		exit(0);
	}
	if(pollution_tab.size() != 0){
		if(q == last_eau() ){
				//! si toutes les cases ont avancées, alors on peut disperser les polluant
			dispersion(1);
		}
	}
								
}
void simulation_non_conforme(int w){
	int x = riviere.getTableau()[w].getX();
	int z = riviere.getTableau()[w].getZ();
	int hauteur_eau = riviere.getH_eau()-riviere.getH_sol();
	Eau* eau =(Eau*)riviere.getTableau()[w].getMatiere();
	if(z - eau->getProfondeur() + hauteur_eau > riviere.getHauteur()-1 ){
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
		cout << "Ainsi quand x vaut " << x << " ,alors là hauteur d'eau augmente de" << endl;
		cout << "une case et vaut: " << z - eau->getProfondeur() + hauteur_eau + 1 <<endl;
		cout << "La riviere deborde donc !. " << endl;
		
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
			Eau* eau =(Eau*)riviere.getTableau()[w].getMatiere();
			if(	eau->getPolluant() != nullptr){
			}
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
	double vitesse;
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
		pollution_tab.clear();
		if(temps >= seuil_cumule){
			seuil_cumule = seuil_cumule + 1/vitesse;
		}
	}else if(riviere.getPalier() == 1){
	/*!
     * @biref
     * cas palier = 1;
     * */
		for(int w = 0; w < taille; w++ ){
			if(riviere.getTableau()[w].getMatiere() != nullptr){
				if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
					vitesse = riviere.getTableau()[w].getMatiere()->getVitesse();
				}
			}
		}
		if(seuil_cumule == 0.0){
			seuil_cumule = seuil_cumule + 1/vitesse;
		}
		
		for(int w = 0; w < taille; w++ ){
				if(temps >= seuil_cumule){
				ecoulement_transversale(w, temps);
				}
		}
		pollution_tab.clear();
		if(temps >= seuil_cumule){
			seuil_cumule = seuil_cumule + 1/vitesse;
		}
	}else{ 
			/*!
			* @biref
			* si la rivière à un palier autre que un
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
				for(int w = taille - caseRestante; w < taille; w++){
					if(riviere.getTableau()[w].getMatiere()== nullptr){;
						if(temps >= seuil_cumule){
							ecoulementPlat(w, temps);
						}
					}else if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
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
										if(last_eau() == -1){
											cout << "----------------------" << endl;
											cout << "Erreur, il n'y a pas de" << endl;
											cout << "case eau ." << endl;
											cout << "----------------------" << endl;
											exit(0);
										}
										if(pollution_tab.size() != 0){
											if(w == last_eau() ){
												dispersion(1);
																}
										}
								}
							}
						}
					}
				
					
				}
				pollution_tab.clear();
				if(temps >= seuil_cumule){
					seuil_cumule = seuil_cumule + 1/vitesse;			
				}
			
		}
	return Py_BuildValue("i",0);
}

int zmax_eau(){
	int xmax = riviere.getLongueur()-1;
	int z_max = 0;
	for(int w = taille -1; w >= taille - (riviere.getLargeur()*riviere.getLongueur()); w--){
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				z_max = (w -xmax*riviere.getLargeur() * riviere.getHauteur())/riviere.getLargeur();
				break;
			}
		}
	return z_max;
}
static PyObject * pollution(PyObject * self, PyObject * args){
	int pollution_state;
	int w = 0;
	int z_maxEau = 0;
	if (! PyArg_ParseTuple(args, "i", &pollution_state)) return NULL;
	if(pollution_state == 1){
		z_maxEau = zmax_eau();
		w = rand() % riviere.getLargeur() + taille - (riviere.getHauteur()- z_maxEau) * riviere.getLargeur(); 
		Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
		eau_pollu->setPolluant("fer", 10, riviere.getLongueur() -1, eau_pollu->getVitesse());
	}else if (pollution_state == 2){
		z_maxEau = zmax_eau();
		w = rand() % riviere.getLargeur() + taille - (riviere.getHauteur()- z_maxEau) * riviere.getLargeur();
		Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
		eau_pollu->setPolluant("phosphore", 10, riviere.getLongueur() -1, eau_pollu->getVitesse());
  
	}else if (pollution_state == 3){
		z_maxEau = zmax_eau();
		w = rand() % riviere.getLargeur() + taille - (riviere.getHauteur()- z_maxEau) * riviere.getLargeur();
		Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
		eau_pollu->setPolluant("ammoniac", 10, riviere.getLongueur() -1, eau_pollu->getVitesse());
	}
	
return Py_BuildValue("i",0);
}

static PyObject * coord_X(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* m;
	char* nom;
	if (! PyArg_ParseTuple(args, "ss", &m, &nom)) return NULL;
	string matiere = m;
	string polluant = nom;
	if(matiere == "EAU_POLLUE"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					if(eau_pollu->getPolluant()->getNom() == polluant){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
					}
				}	
			}
		}
	}else if(matiere == "EAU"){
			for(int w = 0; w < taille; w++){
				if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
					Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
					if(eau_pollu->getPolluant() == nullptr){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
					}
				}
			}
	}else{ 
		for(int w = 0; w < taille; w++){
				if(riviere.getTableau()[w].getMatiere()->getType() == matiere){	
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
			}
		}
	}
	return data_animation;
}
static PyObject * coord_Y(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* m;
	char* nom;
	if (! PyArg_ParseTuple(args, "ss", &m, &nom)) return NULL;
	string matiere = m;
	string polluant = nom;
	if(matiere == "EAU_POLLUE"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					if(eau_pollu->getPolluant()->getNom() == polluant){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
					}
				}	
			}
		}
	}else if(matiere == "EAU"){
			for(int w = 0; w < taille; w++){
				if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
					Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
					if(eau_pollu->getPolluant() == nullptr){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
					}
				}
			}
	}else{ 
		for(int w = 0; w < taille; w++){
				if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
			}
		}
	}	
	return data_animation;
}
static PyObject * coord_Z(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* m;
	char* nom;
	if (! PyArg_ParseTuple(args, "ss", &m, &nom)) return NULL;
	string matiere = m;
	string polluant = nom;
	if(matiere == "EAU_POLLUE"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					if(eau_pollu->getPolluant()->getNom() == polluant){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
					}
				}	
			}
		}
	}else if(matiere == "EAU"){
			for(int w = 0; w < taille; w++){
				if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
					Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
					if(eau_pollu->getPolluant() == nullptr){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
					}
				}
			}
	}else{ 
		for(int w = 0; w < taille; w++){
				if(riviere.getTableau()[w].getMatiere()->getType() == matiere){	
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
			}
		}
	}
	return data_animation;
}
static PyObject * getCouleur(PyObject * self, PyObject * args){
	char* m;
	if (! PyArg_ParseTuple(args, "s", &m)) return NULL;
	string matiere = m;
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getMatiere()->getCouleur()));
		}
	}
	return data_animation;
}

static PyObject * getCouleur_eau(PyObject * self, PyObject * args){
	char* m;
	char* nom;
	if (! PyArg_ParseTuple(args, "ss", &m, &nom)) return NULL;
	string matiere = m;
	string polluant = nom;
	PyObject * data_animation = PyList_New(0);
	if(matiere == "EAU_POLLUE"){
		for(int w = 0; w < taille; w++){	
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
				if(eau_pollu->getPolluant() != nullptr){
					if(eau_pollu->getPolluant()->getNom() == polluant){
						PyList_Append(data_animation, Py_BuildValue("i",eau_pollu->getPolluant()->getCouleur()));
					}
				}	
			}
		}	
	}else{
		for(int w = 0; w < taille; w++){
			if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
					Eau* eau_pollu =(Eau*)riviere.getTableau()[w].getMatiere();
					if(eau_pollu->getPolluant() == nullptr){
						PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getMatiere()->getCouleur()));
					}
			}	
		}
	}
	return data_animation;
}
static PyObject * writeCsv(PyObject * self, PyObject * args){
	char* n;
	if (! PyArg_ParseTuple(args, "s", &n)) return NULL;
	string nom = n;
	riviere.writeCSV(nom);
	return  Py_BuildValue("i",0);
}
static PyObject * Cmap(PyObject * self, PyObject * args){
	char* p;
	if (! PyArg_ParseTuple(args, "s", &p)) return NULL;
	string polluant = p;
	PyObject * data_animation = PyList_New(0);
	if(polluant == "fer"){
  		return Py_BuildValue("s","Reds");
	}
	if(polluant == "phosphore"){
  		return Py_BuildValue("s","Greens");
	}
	if(polluant == "ammoniac"){
  		return Py_BuildValue("s","Oranges");
	}
	cout << "return 0" << endl;
	return  Py_BuildValue("i",0);
}

static PyMethodDef methods[] = {
	{"initialisation", initialisation, METH_VARARGS, "Initialisation de environnement riviere."},
	{"ecoulement", ecoulement, METH_VARARGS, "Fait avancer les cases EAU"},
	{"pollution", pollution, METH_VARARGS,"Propage les polluants dans l'eau"},
	{"coord_X", coord_X, METH_VARARGS, "Les coordonnee x de matieres"},
	{"coord_Y", coord_Y, METH_VARARGS, "Les coordonnee y de matieres"},
	{"coord_Z", coord_Z, METH_VARARGS, "Les coordonnee z de matieres"},
	{"getCouleur", getCouleur, METH_VARARGS, "Les couleurs des cases de sol et de l'air"},
	{"getCouleur_eau", getCouleur_eau, METH_VARARGS, "Les couleurs des cases d'eau"},
	{"writeCsv", writeCsv, METH_VARARGS, "Fonction écrit un csv des données"},
	{"Cmap", Cmap, METH_VARARGS, "Les couleurs de polluant"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduleDefinition = {
    PyModuleDef_HEAD_INIT,
    "Noyau",
    "Simulation d une riviere.", 
    -1, 
    methods
};
	
PyMODINIT_FUNC
PyInit_Noyau(void) {
	PyObject * module = PyModule_Create(&moduleDefinition);

    return module;
}

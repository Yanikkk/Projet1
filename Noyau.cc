#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
using namespace std;
#include "Env.hpp"
#include "Eau.hpp"
#include <array>

Env riviere(0,0,0);
int taille = 0;

static PyObject * initialisation(PyObject * self, PyObject * args){
	int largeur;
	int hauteur;
	int longueur;
	if (! PyArg_ParseTuple(args, "iii", &largeur, &hauteur, &longueur)) return NULL;
	Env tampon(largeur, hauteur, longueur);
	taille = largeur * hauteur * longueur;
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

void ecoulementPlat(int w){
	int crossSection = riviere.getLargeur()*riviere.getHauteur();
		if(w/(crossSection)-1 < 0){
			cleanFirstline(w);
		}else{
			int profondeur;
			if(riviere.getTableau()[w - crossSection].getMatiere() == nullptr){	
				profondeur = calculeProfondeur(w - crossSection);
				riviere.getTableau()[w - crossSection].setMatiere(riviere.getTableau()[w].getMatiere());
				riviere.getTableau()[w - crossSection].getMatiere()->setProfondeur(profondeur);
				//cout << "case enlevée: "<< w << endl;
				//cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;
				//cout <<"type de la case enelvée: " << riviere.getTableau()[w].getMatiere()->getType() << endl;
				//cout << " profondeur transmise "<< riviere.getTableau()[w].getMatiere()->getProfondeur() << endl;
				riviere.getTableau()[w].setMatiere(nullptr);
				//cout << "case remise : " << w - crossSection<< endl;
				//cout << "couleur de la case remise: "<<riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())].getMatiere()->getCouleur()<< endl;	
				//cout << " profondeur transmise "<< riviere.getTableau()[w-crossSection].getMatiere()->getProfondeur() << endl;					
			if(w/(crossSection) == riviere.getLongueur()-1){
				if(riviere.getTableau()[w].getMatiere() == nullptr){
					profondeur = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,profondeur));
					//cout << "case remiseeeee : " << w << endl;
					//cout << "couleur de la case remise: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;	
					//cout << " profondeur "<< prof << endl;
				}
			}
		}
	}
}


void ecoulementPalier(int w){
	int crossSection = riviere.getLargeur()*riviere.getHauteur();
		if(w/(crossSection)-1 < 0){
			cleanFirstline(w);
		}
			int profondeur;
			if(riviere.getTableau()[w - crossSection].getMatiere() == nullptr){	
				profondeur = calculeProfondeur(w - crossSection);
				riviere.getTableau()[w - crossSection].setMatiere(riviere.getTableau()[w].getMatiere());
				riviere.getTableau()[w - crossSection].getMatiere()->setProfondeur(profondeur);
				//cout << "case enlevée: "<< w << endl;
				//cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;
				//cout <<"type de la case enelvée: " << riviere.getTableau()[w].getMatiere()->getType() << endl;
				//cout << " profondeur transmise "<< riviere.getTableau()[w].getMatiere()->getProfondeur() << endl;
				riviere.getTableau()[w].setMatiere(nullptr);
				//cout << "case remise : " << w - crossSection<< endl;
				//cout << "couleur de la case remise: "<<riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())].getMatiere()->getCouleur()<< endl;	
				//cout << " profondeur transmise "<< riviere.getTableau()[w-crossSection].getMatiere()->getProfondeur() << endl;					
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

void ecoulement_transversale(int w, int crossSection){
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
				riviere.getTableau()[w].getMatiere()->setProfondeur(profondeur);
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

void parPalier(int q, int w, double temps, double seuil_cumule, int crossSection, double vitesse) {
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
											//cout << " profondeur transmise "<< riviere.getTableau()[q-crossSection].getMatiere()->getProfondeur() << endl;
											riviere.getTableau()[q - (crossSection)].getMatiere()->setProfondeur(profondeur);
											//cout << "case enlevée: "<< q << endl;
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
												riviere.getTableau()[q].getMatiere()->setProfondeur(profondeur);
												//cout << "case enlevée : " << position << endl;
												//cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;	
												riviere.getTableau()[position].setMatiere(nullptr);
												}											
											}
										}
									}

								}
}
void simulation_non_conforme(int w, int crossSection){
	int x = w/crossSection;
	int z = (w -x * riviere.getLargeur() * riviere.getHauteur()) / riviere.getLargeur();
	int hauteur_eau = riviere.getH_eau()-riviere.getH_sol();
	if(z - riviere.getTableau()[w].getMatiere()->getProfondeur() + hauteur_eau > riviere.getHauteur()){
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
		cout << "on a une hauteur d'eau de :" << z - riviere.getTableau()[w].getMatiere()->getProfondeur() + hauteur_eau  << endl;
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

double seuil_cumule = 0.0;
static PyObject * ecoulement(PyObject * self, PyObject * args){
	int crossSection = riviere.getLargeur() * riviere.getHauteur();	
	int last_w = 0;
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
			simulation_non_conforme(w, crossSection);
		}
	}
	if(riviere.getTableau()[taille-1].getMatiere()->getType() == "SOL"){
		erreur_de_palier();
	}
	
	double temps;
	double vitesse = 0;
	if (! PyArg_ParseTuple(args, "d", &temps)) return NULL;
	//le nombre de seconde pour que une case d'eau avance de 1 case
	//cas si la rivière est plus petite que un palier
	//(donc si elle est plate)
	if(riviere.getPalier() >= taille/crossSection){
		for(int w = 0; w < taille; w++){
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				vitesse = riviere.getTableau()[w].getMatiere()->getVitesse();
				if(seuil_cumule == 0.0){
					seuil_cumule = seuil_cumule + 1/vitesse;
				}
				if(temps >= seuil_cumule){
					ecoulementPlat(w);
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
							parPalier(q,w, temps, seuil_cumule, crossSection, vitesse);
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
					ecoulement_transversale(w, crossSection);
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
						parPalier(q,w, temps, seuil_cumule, crossSection, vitesse);
				}
			}
				for(int w = taille - caseRestante + crossSection; w < taille; w++){
					if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
						vitesse = riviere.getTableau()[w].getMatiere()->getVitesse();
						if(temps >= seuil_cumule){
							ecoulementPlat(w);
						}
					}
				}
				if(caseRestante = crossSection){
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
/*
static PyObject * pollution(PyObject * self, PyObject * args){
	int pollution_state;
	if (! PyArg_ParseTuple(args, "i", &pollution_state)) return NULL;
	
	int z_maxEau = 0;
	int xmax = riviere.getLongueur()-1;
	//cas du Fer par exemple
	if(pollution_state == 1){
		for(int w = taille -1; w >= taille - (riviere.getLargeur*getLongueur()); w--){
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				z_maxEau = (w -xmax*riviere.getLargeur() * riviere.getHauteur())/riviere.getLargeur();
				break;
			}
		}
		//génère un nombre sur la dernière ligne d'eau de la dernière crossSection de la simulation
		w = rand() % (get.Largeur()-1) + taille - (getHauteur()-1- zmax) * getLargeur(); 
		//riviere.getTableau()[w].getMatiere()->setPolluant("fer",)
	}
	
	
	
return Py_BuildValue("i",0);
}*/


static PyObject * coord_X(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* matiere;
	if (! PyArg_ParseTuple(args, "s", &matiere)) return NULL;
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
		}
	}
	return data_animation;
}
static PyObject * coord_Y(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* matiere;
	if (! PyArg_ParseTuple(args, "s", &matiere)) return NULL;
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
		}
	}
	return data_animation;
}
static PyObject * coord_Z(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	char* matiere;
	if (! PyArg_ParseTuple(args, "s", &matiere)) return NULL;
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == matiere){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
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
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getMatiere()->getCouleur()));
		}
	}
	return data_animation;
}
//iii = int int intn
//liste python marche mais gourmand
//autre possibilité renvoyer un numpy

static PyMethodDef methods[] = {
	{"initialisation", initialisation, METH_VARARGS, "Initialisation de environnement riviere."},
	{"ecoulement", ecoulement, METH_VARARGS, "Fait avancer les cases EAU"},
	{"coord_X", coord_X, METH_VARARGS, "Les coordonnee x de matieres"},
	{"coord_Y", coord_Y, METH_VARARGS, "Les coordonnee y de matieres"},
	{"coord_Z", coord_Z, METH_VARARGS, "Les coordonnee z de matieres"},
	{"getCouleur_sol", getCouleur_sol, METH_VARARGS, "Les couleurs des cases de sol"},
	{"getCouleur_air", getCouleur_air, METH_VARARGS, "Les couleurs des cases d'air"},
	{"getCouleur_eau", getCouleur_eau, METH_VARARGS, "Les couleurs des cases d'eau"},
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

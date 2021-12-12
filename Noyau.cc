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
			int prof;
			if(riviere.getTableau()[w - crossSection].getMatiere() == nullptr){	
				prof = calculeProfondeur(w - crossSection);
				riviere.getTableau()[w - crossSection].setMatiere(riviere.getTableau()[w].getMatiere());
				riviere.getTableau()[w - crossSection].getMatiere()->setProfondeur(prof);
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
					prof = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,prof));
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
			int prof;
			if(riviere.getTableau()[w - crossSection].getMatiere() == nullptr){	
				prof = calculeProfondeur(w - crossSection);
				riviere.getTableau()[w - crossSection].setMatiere(riviere.getTableau()[w].getMatiere());
				riviere.getTableau()[w - crossSection].getMatiere()->setProfondeur(prof);
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
					prof = calculeProfondeur(w);
					riviere.getTableau()[w].setMatiere(riviere.creation(w,prof));
					//cout << "case remiseeeee : " << w << endl;
					//cout << "couleur de la case remise: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;	
					//cout << " profondeur "<< prof << endl;
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
									lastcrossSection = lastcrossSection / crossSection -1;
									if(q/(crossSection) < lastcrossSection  && state == 1){
										ecoulementPalier(q);
									}
									if(q/(crossSection) == lastcrossSection && state == 1){
										if(riviere.getTableau()[q].getMatiere() !=nullptr){
											riviere.getTableau()[q- (crossSection)].setMatiere(riviere.getTableau()[q].getMatiere());
											profondeur = calculeProfondeur(q-(crossSection));
											//cout << "case remise : " << q-crossSection << endl;
											//cout << "couleur de la case remise: "<<riviere.getTableau()[q-crossSection].getMatiere()->getCouleur()<< endl;	
											//cout << " profondeur calculée "<< prof << endl;
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
												//cout << "fincase enlevée : " << position << endl;
												riviere.getTableau()[position].setMatiere(nullptr);
												}											
											}
										}
									}
								}
}
void simulation_non_conforme(int w, int crossSection){
	int x = w/crossSection;
	int z = (w -x) / riviere.getLargeur();
	int hauteur_eau = riviere.getH_eau()-riviere.getH_sol();
	if(z + hauteur_eau > riviere.getHauteur()){
		cout << "\n\nErreur due a une taille non conforme de la simulation" << endl;
		cout << "Veuillez tenir compte du fait que l'eau ne doit pas deborder" << endl;
		cout << "Pour rappel voici: \n" << endl;
		cout << "Le palier :" << riviere.getPalier() << endl;
		cout << "La largeur :" << riviere.getLargeur() << endl;
		cout << "La longueur :" << riviere.getLongueur() << endl;
		cout << "La hauteur :" << riviere.getHauteur() << endl;
		exit(0);
	}
}

double seuil_cumule = 0.0;
static PyObject * ecoulement(PyObject * self, PyObject * args){
	int crossSection = riviere.getLargeur() * riviere.getHauteur();	
	for(int w = 0; w < taille; w++){
	//simulation_non_conforme(w, crossSection);
	}
	
	double temps;
	double seuil;
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
	}else if(riviere.getLongueur() % riviere.getPalier() == 0){ 
	/*!
     * @biref
     * si la rivière à une pente et si le palier sépare la rivière en partie égale
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
	}else{
			/*!
			* @biref
			* si la rivière à une pente et si le palier ne sépare pas la rivière en partie égale
			* */
			for(int w = 0; w <= taille; w += crossSection * riviere.getPalier()){
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
			if(1==1){
				int caseRestante = taille %(crossSection * riviere.getPalier());
				for(int w = taille - caseRestante; w < taille; w++){
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
			}
		}
	return Py_BuildValue("i",0);
}

static PyObject * coord_Xeau(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
		}
	}
	return data_animation;
}
static PyObject * coord_Yeau(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
		}
	}
	return data_animation;
}
static PyObject * coord_Zeau(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
		}
	}
	return data_animation;
}
static PyObject * coord_Xsol(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "SOL"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
		}
	}
	return data_animation;
}
static PyObject * coord_Ysol(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "SOL"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
		}
	}
	return data_animation;
}
static PyObject * coord_Zsol(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "SOL"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
		}
	}
	return data_animation;
}
static PyObject * coord_Xair(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "AIR"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
		}
	}
	return data_animation;
}
static PyObject * coord_Yair(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille ; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "AIR"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
		}
	}
	return data_animation;
}
static PyObject * coord_Zair(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "AIR"){
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
	{"coord_Xeau", coord_Xeau, METH_VARARGS, "Les coordonnee x des cases contenant de l eau"},
	{"coord_Yeau", coord_Yeau, METH_VARARGS, "Les coordonnee y des cases contenant de l eau"},
	{"coord_Zeau", coord_Zeau, METH_VARARGS, "Les coordonnee z des cases contenant de l eau"},
	{"coord_Xsol", coord_Xsol, METH_VARARGS, "Les coordonnee x des cases contenant de l sol"},
	{"coord_Ysol", coord_Ysol, METH_VARARGS, "Les coordonnee y des cases contenant de l sol"},
	{"coord_Zsol", coord_Zsol, METH_VARARGS, "Les coordonnee z des cases contenant de l sol"},
	{"coord_Xair", coord_Xair, METH_VARARGS, "Les coordonnee x des cases contenant de l air"},
	{"coord_Yair", coord_Yair, METH_VARARGS, "Les coordonnee y des cases contenant de l air"},
	{"coord_Zair", coord_Zair, METH_VARARGS, "Les coordonnee z des cases contenant de l air"},
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

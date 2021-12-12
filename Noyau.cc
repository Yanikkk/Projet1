#define PY_SSIZE_T_CLEAN
#include <Python.h>
//le main est pas nécessaire mtn (devient une bibliothèques
#include <iostream>
using namespace std;
#include "Env.hpp"
#include "Eau.hpp"
#include <array>
// avec ça normalement c'est toujours le même
//sinon en faire un pointeur
Env riviere(0,0,0);
int taille = 0;

static PyObject * initialisation(PyObject * self, PyObject * args){
	//std::cout<<"Noyau_a"<<std::endl;
	int largeur;
	int hauteur;
	int longueur;
	if (! PyArg_ParseTuple(args, "iii", &largeur, &hauteur, &longueur)) return NULL;
	Env tampon(largeur, hauteur, longueur);
	taille = largeur * hauteur * longueur;
	riviere = tampon;
	riviere.copy(&tampon);
	//std::cout<<"Noyau_b"<<std::endl;
	//delete [] tampon.getTableau();
	riviere.initTableau();
	//riviere.writeCSV();
	
	/*
	//utiliser cette fonction pour écrire un csv à un moment t

//source utile
//https://docs.python.org/3/c-api/list.html
//http://web.mit.edu/people/amliu/vrut/python/ext/buildValue.html

	
	riviere.getTableau()[i].matiere_.getvitesse()*/
	return Py_BuildValue("i",0);
}

void cleanFirstline(int w){
	cout << "case enlevée: "<< w << endl;
	cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;
	cout <<"type de la case enelvée: " << riviere.getTableau()[w].getMatiere()->getType() << endl;
				
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
		//si ce sont les premières cases tout devant en x = 0
		if(w/(crossSection)-1 < 0){
			cleanFirstline(w);
		}else{
			//si les cases devant sont nullptr
			//alors les matières avancent
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
		//vérifie si il ne s'agit pas des dernières cases
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


void ecoulementPlatPalier(int w){
	int crossSection = riviere.getLargeur()*riviere.getHauteur();
		//si ce sont les premières cases tout devant en x = 0
		if(w/(crossSection)-1 < 0){
			cleanFirstline(w);
		}
			//si les cases devant sont nullptr
			//alors les matières avancent
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
		//vérifie si il ne s'agit pas des dernières cases
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




double seuil_cumule = 0.0;
static PyObject * ecoulement(PyObject * self, PyObject * args){
	double temps;
	double seuil;
	if (! PyArg_ParseTuple(args, "d", &temps)) return NULL;
	//le nombre de seconde pour que une case d'eau avance de 1 case
	int crossSection = riviere.getLargeur() * riviere.getHauteur();	
	//cas si la rivière est plus petite que un palier
	//(donc si elle est plate)
	if(riviere.getPalier() >= taille/crossSection){
		for(int w = 0; w < taille; w++){
			double vitesse = riviere.getTableau()[w].getMatiere()->getVitesse();
			if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
				seuil =  1/vitesse;
				if(temps >= seuil){ //soustraire le temps depuis la dernière fois
					seuil_cumule = seuil_cumule + 1/vitesse;
					seuil = seuil_cumule;
					ecoulementPlat(w);
				}
			}
		}
	}else{ 
		//si la rivière à une pente
		
		//état de l'attribution au mouvement des cases
		//état 0 => on traite les cases en première ligne
		//état 1 => on traite les cases en non situation de débordement
		//état 2 => se met en place quand il y a un état de dépacement
	
		//l'état de dépacement est caractériser par une hauteur de l'eau réel qui sortirai de notre tableau
		//de simulation
		//Cela entraîne la nécessité de faire directement "nâitre" certaine cases d'eau sur le dessus de notre simulation.
		int state = 0;
		int prof = 0;
		int state_depacement = 0;
		int lastcrossSection = 0;
		int profond_actuelle = 0;
		int profond_apres = 0;
		int h_chgmnt_palier = 0;
		int position = 0;
		int xprof = 0;
		int zmax = 0;
		//faire si le palier ne sépare pas en partie 
		//finit avec de l'eau 
		//ou finit avec du sol
		
		//si le palier sépare la rivière en partie égale
		if(taille % riviere.getPalier() == 0){
			for(int w = 0; w <= taille - crossSection * riviere.getPalier(); w += crossSection * riviere.getPalier()){
				for(int q = w; q < w+crossSection * riviere.getPalier(); q++){
				//vérifier état débordement			if(
					//		state_depacement = 1
					double vitesse = 0;
					if(riviere.getTableau()[q].getMatiere() != nullptr){
						vitesse = riviere.getTableau()[q].getMatiere()->getVitesse();
					}else{ continue;}
					
					if(riviere.getTableau()[q].getMatiere()->getType() == "EAU"){
						seuil =  1/vitesse;
							if(temps >= seuil){ //soustraire le temps depuis la dernière fois
								seuil_cumule = seuil_cumule + 1/vitesse;
								seuil = seuil_cumule;
								
					//pas en état de dépacement
								if(state_depacement == 0){
						//état 0	
									if((q/(crossSection))-1 < 0 && state == 0){
										cleanFirstline(q);
									}
									if((q/(crossSection))-1 >=0 && state == 0){
										state = 1;
									}

						//état 1
						//concerne toutes les cases du palier sauf la dernière crossSection
									lastcrossSection = w+crossSection * riviere.getPalier();
									lastcrossSection = lastcrossSection / crossSection -1;
									if(q/(crossSection) < lastcrossSection  && state == 1){
										ecoulementPlatPalier(q);
									}
						//si on est sur la dernière crossSection du palier
								if(q/(crossSection) == lastcrossSection && state == 1){
							// les cases de la dernière crossSection qu'il faut encore
							//transférer à l'avant dernière crossSection sont transféré
										if(riviere.getTableau()[q].getMatiere() !=nullptr){
											riviere.getTableau()[q- (crossSection)].setMatiere(riviere.getTableau()[q].getMatiere());
											prof = calculeProfondeur(q-(crossSection));
											//cout << "case remise : " << q-crossSection << endl;
											//cout << "couleur de la case remise: "<<riviere.getTableau()[q-crossSection].getMatiere()->getCouleur()<< endl;	
											//cout << " profondeur calculée "<< prof << endl;
											//cout << " profondeur transmise "<< riviere.getTableau()[q-crossSection].getMatiere()->getProfondeur() << endl;
											riviere.getTableau()[q - (crossSection)].getMatiere()->setProfondeur(prof);
											//cout << "case enlevée: "<< q << endl;
											//cout << "couleur de la case enlevée: "<<riviere.getTableau()[q].getMatiere()->getCouleur()<< endl;
											//cout <<"type de la case enelvée: " << riviere.getTableau()[q].getMatiere()->getType() << endl;
				
											riviere.getTableau()[q].setMatiere(nullptr);
										}
								// si la case sur la dernière crossSection est vide 
								//(donc a déjà été transféré)
											if(riviere.getTableau()[q].getMatiere() == nullptr){
									//si on a atteint la dernière case de la dernière
									//cross Section du tableau
												if(q/crossSection == riviere.getLongueur() -1){
														ecoulementPlatPalier(q);
												}
												if(q/crossSection != riviere.getLongueur() -1){//il reste encore des paliers derrière
									//on prend la première ligne du prochain palier et on la transmet
									// à la dernière ligne du palier actuelle
									//position de la case à transmettre
							
									//on calcule la hauteur du changemnent de palier
									
									//on a les coord. x de la crossSection en cours
									//et on a le z max du tableau
												xprof = q/crossSection;
												zmax= riviere.getHauteur();
												//cout << "xprof : " << xprof  << endl;
												//cout << "zmax " << 	zmax << endl;
									// on calcule la distance du sol par rapport à tout en haut
												//cout << xprof*crossSection+ zmax*riviere.getLargeur() -1 << endl;
												//cout << (xprof+1)*crossSection + zmax*riviere.getLargeur()-1 << endl;
												profond_actuelle = calculeProfondeur(xprof*crossSection+ zmax*riviere.getLargeur()-1);
												profond_apres = calculeProfondeur((xprof+1)*crossSection + zmax*riviere.getLargeur()-1);
												//cout << "profondeur actuelle: " << profond_actuelle << endl;
												//cout << "pprofond_apres " << profond_apres << endl;
												h_chgmnt_palier = profond_actuelle - profond_apres;
												position = q + h_chgmnt_palier *riviere.getLargeur() + (crossSection);
									//on transfère cette matière
												cout << position << endl;
												//cout << "case ajoutée : " << q << endl;
												//cout << "couleur de la case ajoutée: "<<riviere.getTableau()[position].getMatiere()->getCouleur()<< endl;	
												riviere.getTableau()[q].setMatiere(riviere.getTableau()[position].getMatiere());
												prof = calculeProfondeur(q);
												riviere.getTableau()[q].getMatiere()->setProfondeur(prof);
								// et cette matière devient nulle
												//cout << "case enlevée : " << position << endl;
												//cout << "couleur de la case enlevée: "<<riviere.getTableau()[w].getMatiere()->getCouleur()<< endl;	
												//cout << "fincase enlevée : " << position << endl;
												riviere.getTableau()[position].setMatiere(nullptr);
												//si on a atteint la dernière case de la dernière
									//cross Section du tableau
				
												}											
											}
									}
								}
					
							}
							
						}
					}
				}
			}	
		}
	return Py_BuildValue("i",0);
}

static PyObject * coord_Xeau(PyObject * self, PyObject * args){
	//riviere.writeCSV();
	PyObject * data_animation = PyList_New(0);
	//renvoie la position des cases d'eau en x
	//std::cout<<"taille après:"<< taille <<std::endl;
	for(int w = 0; w < taille; w++){
		if(riviere.getTableau()[w].getMatiere()->getType() == "EAU"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
		}
	}
	return data_animation;
}
static PyObject * coord_Yeau(PyObject * self, PyObject * args){
	//riviere.writeCSV();
	PyObject * data_animation = PyList_New(0);
	//cout <<"taille verification" << taille << endl;
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

/*
int main() {

	Env riviere(20,30,40);
	// créer un objet Env avec les dimensions x, y, z passées en paramètres.
	// 40,60,200
	riviere.initTableau();
	riviere.writeCSV();
	// delete[] tableau_; // pas oublier de supprimer le tableau -> ici ?
	return 0;
}
*/

#define PY_SSIZE_T_CLEAN
#include <Python.h>
//le main est pas nécessaire mtn (devient une bibliothèques
#include <iostream>
using namespace std;
#include "Env.hpp"
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
	riviere = tampon;
	riviere.copy(&tampon);
	//std::cout<<"Noyau_b"<<std::endl;
	//delete [] tampon.getTableau();
	riviere.initTableau();
	/*//riviere.writeCSV();
	//utiliser cette fonction pour écrire un csv à un moment t

//source utile
//https://docs.python.org/3/c-api/list.html
//http://web.mit.edu/people/amliu/vrut/python/ext/buildValue.html

	
	riviere.getTableau()[i].matiere_.getvitesse()*/
	//cout << "Noyau_c" << endl;
	return Py_BuildValue("i",0);
}
//fait avancer les cases d'eau
double seuil_cumule = 0.0;
static PyObject * ecoulement(PyObject * self, PyObject * args){
	double temps;
	//cout << "Noyau_d" << endl;
	if (! PyArg_ParseTuple(args, "d", &temps)) return NULL;
	//le nombre de seconde pour que une case d'eau avance de 1 case
	int statut = 0;
	int zb = 0;
	int zd = 0;
	int state_denivele_b = 0;
	int state_denivele_d = 0;
	int hs_dessous = 0;
	int hs_devant = 0;
	cout << "Noyau_e" << endl;
	Matiere* tampon;
	cout << "Noyau_f" << endl;
	taille = riviere.getLargeur() * riviere.getLongueur() * riviere.getHauteur();
	//std::cout<<"taille avant:"<< taille <<std::endl;
	cout << "Noyau_h" << endl;
	for(int w = 0; w < taille; w++){
		std::string type = riviere.getTableau()[w].getMatiere()->getType(); // voir si worse et si ailleur
		double vitesse = riviere.getTableau()[w].getMatiere()->getVitesse();
		cout << "Noyau_g1" << endl;
		if(type == "EAU"){
			cout << "Noyau_g2" << endl;
			double seuil =  1/vitesse;
			if(temps >= seuil){ //soustraire le temps depuis la dernière fois
			seuil_cumule = seuil_cumule + 1/vitesse;
			seuil = seuil_cumule;
				
				if(w/(riviere.getLargeur()*riviere.getHauteur())-1 < 0){ // si ce sont les cases au bords alors elles sortent et sont effacées
					cout << "Noyau_i1" << endl;
					// si il ne fait que une case
					if(riviere.getLongueur() == 1){
						tampon = riviere.creation(w, riviere.getTableau()[w].getMatiere());
						statut = 1;
						cout << "Noyau_i2" << endl;
					}
					cout << "case enlevée première ligne: "<< w << endl;
					cout << "type de la case enlevée:" << riviere.getTableau()[w].getMatiere()->getType() << endl;
					delete riviere.getTableau()[w].getMatiere();
					riviere.getTableau()[w].setMatiere(nullptr);
					if(statut == 1){ // lui renvoit la même
						riviere.getTableau()[w].setMatiere(tampon);
						statut = 0;
					}
					
				} else {
					
						cout << "Noyau_j1" << endl;
					//vérifie si il ne s'agit pas de la dernière case
					if(w/(riviere.getLargeur()*riviere.getHauteur()) == riviere.getLongueur()){
						cout << "Noyau_j2" << endl;
						tampon = new Matiere(*riviere.creation(w, riviere.getTableau()[w].getMatiere()));
						statut = 1;
						
					}
					cout << "Noyau_j3" << endl;
					//trouver si la hauteur de sol à la hauteur x et à la hauteur x -1 est la même ou non
					for(int q = 0; q < riviere.getLargeur()*riviere.getHauteur(); q++){
						if(state_denivele_b == 0){
							cout << "Noyau_j4" << endl;
							if(riviere.getTableau()[w -zb*riviere.getLargeur()].getMatiere() == nullptr){
								zb = zb+1;
								cout << "Noyau_j5" << endl;
								continue;
							}else if(riviere.getTableau()[w -zb*riviere.getLargeur()].getMatiere()->getType() != "SOL"){
								zb = zb+1;
								cout << "Noyau_j6" << endl;
								continue;
							}else if(riviere.getTableau()[w -zb*riviere.getLargeur()].getMatiere()->getType() == "SOL"){
								state_denivele_b = 1;
								cout << "Noyau_j7" << endl;
								continue;
							}
						}
						if(state_denivele_d == 0){
							 cout << "Noyau_jj" << endl;
							if(riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())- zd*riviere.getLargeur()].getMatiere() == nullptr){
								zd = zd+1;
								cout << "Noyau_j8" << endl;
								continue;
							}else if(riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())- zd*riviere.getLargeur()].getMatiere()->getType() != "SOL"){
								zd = zd+1;
								cout << "Noyau_j9" << endl;
								continue;
							}else if(riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())- zd*riviere.getLargeur()].getMatiere()->getType() == "SOL"){
								state_denivele_d = 1;
								cout << "Noyau_j10" << endl;
								continue;
							}
							
						}
						if(state_denivele_b == 1 && state_denivele_d == 1){
							cout << "Noyau_j11" << endl;
							break;
						}
					}
					state_denivele_b = 0;
					state_denivele_d = 0;
					hs_dessous = zb;
					hs_devant = zd;
					zb = 0;
					zd = 0;
					cout << "Noyau_k2" << endl;
					// si la case devant elle est vide et que le sol est plat
					if(riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())].getMatiere() == nullptr && hs_dessous == hs_devant){	
						riviere.getTableau()[w - (riviere.getLargeur()*riviere.getHauteur())].setMatiere(riviere.getTableau()[w].getMatiere()); // elle devient cette matière
						cout << "case enlevée: "<< w << endl;
						cout <<"type de la case enelvée: " << riviere.getTableau()[w].getMatiere()->getType() << endl;
						riviere.getTableau()[w].setMatiere(nullptr);
						cout << "case remise : " << w - (riviere.getLargeur()*riviere.getHauteur())<< endl;
						if(statut == 1){
							riviere.getTableau()[w].setMatiere(tampon);
							statut = 0;
							cout << "Noyau_k3" << endl;
						}
					}
					//pour l'instant la seul situation c'est que le sol devant est de une case plus bas alors j'écris ça comme ça
					if(hs_dessous != hs_devant && 1 == hs_dessous - hs_devant){
						cout << "Noyau_L" << endl;
						if(riviere.getTableau()[w - riviere.getLargeur() - (riviere.getLargeur()*riviere.getHauteur())].getMatiere() == nullptr){
							// il s'agit ici de la case devant(en x) et un cran en dessous(en z)
							riviere.getTableau()[w - riviere.getLargeur() - (riviere.getLargeur()*riviere.getHauteur())].setMatiere(riviere.getTableau()[w].getMatiere());
							cout << "case enlevée: "<< w << endl;
							cout << "case remise : " << w - (riviere.getLargeur()*riviere.getHauteur())<< endl;
							riviere.getTableau()[w].setMatiere(nullptr); // la précédente se fait effacer
						cout << "Noyau_M" << endl;
						}
						if(statut == 1){
							cout << "case crée à la fin: " << w <<endl;
							riviere.getTableau()[w].setMatiere(tampon);
							statut = 0;
							cout << "Noyau_N" << endl;
						}
					}
				}
			}
		}
	}
		cout << "Noyau_l" << endl;
	tampon = nullptr;
	return Py_BuildValue("i",0);
}

static PyObject * coord_Xeau(PyObject * self, PyObject * args){
	//riviere.writeCSV();
	//	taille = riviere.getLargeur() * riviere.getLongueur() * riviere.getHauteur();
	//cout << "Noyau_e" << endl;
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

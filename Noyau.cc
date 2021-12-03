#define PY_SSIZE_T_CLEAN
#include <Python.h>
//le main est pas nécessaire mtn (devient une bibliothèques
#include <iostream>
#include "Env.hpp"

// avec ça normalement c'est toujours le même
//sinon en faire un pointeur
Env riviere(0,0,0);

static PyObject * initialisation(PyObject * self, PyObject * args){
	int largeur;
	int hauteur;
	int longueur;
	if (! PyArg_ParseTuple(args, "iii", &largeur, &hauteur, &longueur)) return NULL;
	Env tampon(largeur, hauteur, longueur);
	riviere = tampon;
	delete [] tampon.getTableau();
	riviere.initTableau();
	//riviere.writeCSV();
	//utiliser cette fonction pour écrire un csv à un moment t
	
//source utile
//https://docs.python.org/3/c-api/list.html
//http://web.mit.edu/people/amliu/vrut/python/ext/buildValue.html
/*
	)
	riviere.getTableau()[i].matiere_.getvitesse()*/
	return Py_BuildValue("i",0);
}
//fait avancer les cases d'eau
static PyObject * ecoulement(PyObject * self, Pyobject * args{
	double temps;
	if (! PyArg_ParseTuple(args, "d", &temps)) return NULL;
	//le nombre de seconde pour que une case d'eau avance de 1 case
	
	int z = 0;
	int hs_dessous = 0;
	int hs_devant = 0;
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "EAU"){
			double seuil =  1/riviere.getTableau()[w].matiere_.getvitesse();
			if(temps >= seuil){ //soustraire le temps depuis la dernière fois
				if(w/(largeur_*hauteur_)-1 < 0){ // si ce sont les cases au bords alors elles sortent et sont effacées
					riviere.getTableau()[w].getMatiere() = "VIDE"; //normalement marche pas
				}
				
				else{
						//trouver si la hauteur de sol à la hauteur x et à la hauteur x -1 est la même ou non
						while(riviere.getTableau()[w -z*riviere.getLargeur()].getMatiere().getType() != "SOL"){
							z = z+1;
						}
						hs_dessous = z;
						z = 0;
						while(riviere.getTableau()[w - (getLargeur()*getHauteur())- z*riviere.getLargeur()].getMatiere().getType() != "SOL"){
							z = z+1;
						}
						hs_devant = z;
						z = 0;
						// si la case devant elle est vide et que le sol est plat
						if(riviere.getTableau()[w - (getLargeur()*getHauteur())].getMatiere() == "VIDE" && hs_dessous == hs_devant){
								riviere.getTableau()[w - (getLargeur()*getHauteur())] = riviere.getTableau()[w]; // elle devient cette case
								delete riviere.getTableau()[w]; // la précédente se fait effacer
								riviere.getTableau()[w] = nullptr;
						}
						//pour l'instant la seul situation c'est que le sol devant est de une case plus bas alors j'écris ça comme ça
						if(hs_dessous != hs_devant && 1 = hs_dessous - hs_devant){
							if(riviere.getTableau()[w - getLargeur - (getLargeur()*getHauteur())].getMatiere() == "VIDE"){
								// il s'agit ici de la case devant(en x) et un cran en dessous(en z)
								riviere.getTableau()[w - getLargeur - (getLargeur()*getHauteur())] = riviere.getTableau()[w]; 
								riviere.getTableau()[w].getMatiere() = "VIDE"; // la précédente se fait effacer
							}
						}
						
				}
			}
		}
	}
	
	return Py_BuildValue("i",0);

}
static PyObject * coord_Xeau(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	//renvoie la position des cases d'eau en x
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
	}
	return data_animation;
}
static PyObject * coord_Yeau(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "EAU"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
		}
	}
	return data_animation;
}
static PyObject * coord_Zeau(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "EAU"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
		}
	}
	return data_animation;
}
static PyObject * coord_Xsol(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "SOL"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
		}
	}
	return data_animation;
}
static PyObject * coord_Ysol(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "SOL"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
		}
	}
	return data_animation;
}
static PyObject * coord_Zsol(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "SOL"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
		}
	}
	return data_animation;
}
static PyObject * coord_Xair(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "AIR"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getX()));
		}
	}
	return data_animation;
}
static PyObject * coord_Yair(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "AIR"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getY()));
		}
	}
	return data_animation;
}
static PyObject * coord_Zair(PyObject * self, PyObject * args){
	PyObject * data_animation = PyList_New(0);
	for(int w = 0; w < sizeof(riviere.getTableau()); w++){
		if(riviere.getTableau()[w].getMatiere().getType() == "AIR"){
			PyList_Append(data_animation, Py_BuildValue("i",riviere.getTableau()[w].getZ()));
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

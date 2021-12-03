#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>
#include "Env.hpp"
//le main est pas nécessaire mtn (devient une bibliothèques

static PyObject * initialisation(PyObject * self, PyObject * args){
	int largeur;
	int hauteur;
	int longueur;
	if (! PyArg_ParseTuple(args, "did", &largeur, &hauteur, &longueur)) return NULL;
	Env riviere(largeur, hauteur, longueur);
	
	return PyFloat_FromDouble(0.0);
}

static PyMethodDef methods[] = {
	{"initialisation", initialisation, METH_VARARGS, "Simulation d une riviere."},
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

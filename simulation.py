#! /usr/bin/python3
import sys
import Noyau
import numpy as np
import matplotlib.pyplot as plt
from maplotlib.animation import FuncAnimation

largeur = 20
hauteur = 30
longueur = 40
	#40,60,200

#initialise le tableau/environnement

Noyau.initialisation(largeur, hauteur, longueur)



def animation_frame(i):
	#fait avancer les cases EAU
	Noyau.ecoulement(i)
	
	#retourne les coordonnées x des cases du tableau contenant l'eau à l'instant i
	Noyau.coordX_eau()
	Noyau.coordY_eau()
	Noyau.coordZ_eau()

	Noyau.coordX_sol()
	Noyau.coordY_sol()
	Noyau.coordZ_sol()

	Noyau.coordX_air()
	Noyau.coordY_air()
	Noyau.coordZ_air()
	
	return,
	
animation = FuncAnimation(fig, func = animation_frame =, frames = np.arrange(0, 10, 0.01), interval = 10)
 

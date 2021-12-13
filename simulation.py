#! /usr/bin/python3
import sys
import Noyau
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import keyboard

largeur = 20
hauteur = 30
longueur = 40

	#avec taille !!! 20,30,40 (ne marche pas au niveau de Case::setX(x) (il ne trouve pas l attribut privé
	#40,60,200
	

#initialise le tableau/environnement

Noyau.initialisation(largeur, hauteur, longueur)

# Graphe 3D
from mpl_toolkits.mplot3d import Axes3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.set_title('Belle rivière !')
ax.set_xlabel('Longueur')
ax.set_xlim(0,40)
ax.set_ylabel('Largeur')
ax.set_ylim(-5,25)
ax.set_zlabel('Hauteur')
ax.set_zlim(0,40)

#retourne les coordonnées x des cases du tableau contenant l'eau à l'instant i
X_eau = np.array(Noyau.coord_X("EAU"))
Y_eau = np.array(Noyau.coord_Y("EAU"))
Z_eau = np.array(Noyau.coord_Z("EAU"))
couleur_eau = np.array(Noyau.getCouleur_eau())

X_sol = np.array(Noyau.coord_X("SOL"))
Y_sol = np.array(Noyau.coord_Y("SOL"))
Z_sol = np.array(Noyau.coord_Z("SOL"))
couleur_sol = np.array(Noyau.getCouleur_sol())

X_air = np.array(Noyau.coord_X("AIR"))
Y_air = np.array(Noyau.coord_Y("AIR"))
Z_air = np.array(Noyau.coord_Z("AIR"))
couleur_air = np.array(Noyau.getCouleur_air())

scatter_sol = ax.scatter(X_sol, Y_sol, Z_sol, c = couleur_sol, cmap = "copper", marker='s', s = 10, alpha=0.3, vmin = 0, vmax = 100)
scatter_air = ax.scatter(X_air, Y_air, Z_air, c = couleur_air, cmap = "jet", marker='s', s = 10, alpha=0.005, vmin = 0, vmax = 100) #voir comment on fait la couleur de l'air avec l'héritage -> alpha = 0,001 l'air disparait
scatter_eau = ax.scatter(X_eau, Y_eau, Z_eau, c = couleur_eau, cmap = "Blues", marker='s', s = 10, alpha=0.2, vmin = 0, vmax = 100)
'''
def setup_plot():
	X_eau = Noyau.coord_Xeau()
	Y_eau = Noyau.coord_Yeau()
	Z_eau = Noyau.coord_Zeau()
	couleur_eau = Noyau.getCouleur_eau()

	X_sol = Noyau.coord_Xsol()
	Y_sol = Noyau.coord_Ysol()
	Z_sol = Noyau.coord_Zsol()
	couleur_sol = Noyau.getCouleur_sol()

	X_air = Noyau.coord_Xair()
	Y_air = Noyau.coord_Yair()
	Z_air = Noyau.coord_Zair()
	#couleur_air = Noyau.getCouleur_air() si on fait ?

	scatter_sol = ax.scatter(X_sol, Y_sol, Z_sol, c = couleur_sol, cmap = "copper", marker='s', s = 10, alpha=0.3, vmin = 0, vmax = 100)
	scatter_air = ax.scatter(X_air, Y_air, Z_air, c = 'skyblue', marker='s', s = 10, alpha=0.002) #voir comment on fait la couleur de l'air avec l'héritage -> alpha = 0,001 l'air disparait
	scatter_eau = ax.scatter(X_eau, Y_eau, Z_eau, c = couleur_eau, cmap = "Blues", marker='s', s = 10, alpha=0.2, vmin = 0, vmax = 100)
	
	scatters = [scatter_sol, scatter_eau, scatter_air]
	print(X_eau)
	return scatters
'''

def change_meteo():
	if keyboard.is_pressed('p'): #pluie
		for i in range(len(couleur_air)): 
			couleur_air[i] = 15
	if keyboard.is_pressed('b'): #brouillard (pas trouver dans cette cmap)
		for i in range(len(couleur_air)): 
			couleur_air[i] = 100
	if keyboard.is_pressed('n'): #nuit
		for i in range(len(couleur_air)): 
			couleur_air[i] = 0
	if keyboard.is_pressed('r'): #sunrise
		for i in range(len(couleur_air)): 
			couleur_air[i] = 90
	if keyboard.is_pressed('s'): #sunset
		for i in range(len(couleur_air)): 
			couleur_air[i] = 75
	if keyboard.is_pressed('w'): #arc-en-ciel
		palier = len(couleur_air)/100
		j = 0
		compteur = 0
		for i in range(len(couleur_air)):
			if compteur > palier :
				compteur = 0 
				j += 1
			compteur += 1
			couleur_air[i] = j
#pollution_state = 0	

def animation_frame(i):
	#fait avancer les cases EAU
	
	#tester si ça arrête et redémarre quand on appuie sur space
	if keyboard.is_pressed('space'):
		keyboard.wait('space')
	
	#Noyau.pollution(pollution_state)
	
	Noyau.ecoulement(i)
	change_meteo()
	X_eau = np.array(Noyau.coord_X("EAU"))
	Y_eau = np.array(Noyau.coord_Y("EAU"))
	Z_eau = np.array(Noyau.coord_Z("EAU"))
	couleur_eau = np.array(Noyau.getCouleur_eau())
	
	X_sol = np.array(Noyau.coord_X("SOL"))
	Y_sol = np.array(Noyau.coord_Y("SOL"))
	Z_sol = np.array(Noyau.coord_Z("SOL"))
	couleur_sol = np.array(Noyau.getCouleur_sol())

	X_air = np.array(Noyau.coord_X("AIR"))
	Y_air = np.array(Noyau.coord_Y("AIR"))
	Z_air = np.array(Noyau.coord_Z("AIR"))
	#couleur_air = Noyau.getCouleur_air() 
	
	scatter_eau._offsets3d = (X_eau, Y_eau, Z_eau)
	scatter_sol._offsets3d = (X_sol, Y_sol, Z_sol)
	scatter_air._offsets3d = (X_air, Y_air, Z_air)
	scatter_eau.set_array(couleur_eau)
	scatter_air.set_array(couleur_air)
	'''
	scatter_eau.stale = True
	scatter_sol.stale = True
	scatter_air.stale = True
	'''
	
	scatters = [scatter_sol, scatter_eau, scatter_air]
	return scatters

animation = FuncAnimation(fig, func=animation_frame, frames=np.arange(0, 10, 0.01), interval=10, blit=False)
plt.show()

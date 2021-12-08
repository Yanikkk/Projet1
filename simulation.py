#! /usr/bin/python3
import sys
import Noyau
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

largeur = 4
hauteur = 6
longueur = 20
	#avec taille !!! 20,30,40 (ne marche pas au niveau de Case::setX(x) (il ne trouve pas l attribut privé
	#40,60,200

#initialise le tableau/environnement

Noyau.initialisation(largeur, hauteur, longueur)

# Graphe 3D

from mpl_toolkits.mplot3d import Axes3D
print("sim_A")
fig = plt.figure()
print("sim_A")
ax = fig.add_subplot(111, projection='3d')
print("sim_A")
X_sol = []
Y_sol = []
Z_sol = []
X_air = []
Y_air = []
Z_air = []
X_eau = []
Y_eau = []
Z_eau = []
#couleur = []



def animation_frame(i):
	#fait avancer les cases EAU
	Noyau.ecoulement(i)
	
	#retourne les coordonnées x des cases du tableau contenant l'eau à l'instant i
	X_sol = Noyau.coordX_eau()
	Y_sol = Noyau.coordY_eau()
	Z_sol = Noyau.coordZ_eau()
	couleur_sol = Noyau.getCouleur_sol()

	X_air = Noyau.coordX_sol()
	Y_air = Noyau.coordY_sol()
	Z_air = Noyau.coordZ_sol()
	#couleur_air = Noyau.getCouleur_air() si on fait ?

	X_eau = Noyau.coordX_air()
	Y_eau = Noyau.coordY_air()
	z_eau = Noyau.coordZ_air()
	# Normal que le z pas en maj ici ??????????????????????????????????????????????????
	couleur_eau = Noyau.getCouleur_eau()
	
	
	
	ax.scatter(X_sol, Y_sol, Z_sol, c = couleur_sol, cmap = "copper", marker='s', s = 10, alpha=0.3)
	ax.scatter(X_air, Y_air, Z_air, c = 'skyblue', marker='s', s = 10, alpha=0.01) #voir comment on fait la couleur de l'air avec l'héritage
	ax.scatter(X_eau, Y_eau, Z_eau, c = couleur_eau, cmap = "blues", marker='s', s = 10, alpha=0.2)
	# ou cmap = plt.cm.get_cmap("blues", 5) le 5 est la séparation de l'échelle des couleurs
	# donc pour si on veut des séparation marquée ou tout continue et donc peut être moins flagrant l'avancée mais plus réelle l'avancée
  
	print("sim_B")
	return ax,
	
animation = FuncAnimation(fig, func = animation_frame, frames = np.arange(0, 10, 0.01), interval = 10)
print("sim_C")
#remplacer les couleurs par cmap ou jsais pas quoi qu'on peut transferer dans le csv.
  # cmap = "blues"
ax.set_title('Wouahouuu ! Belle rivière !')

ax.set_xlabel('Longueur')
ax.set_xlim(0,40)
ax.set_ylabel('Largeur')
ax.set_ylim(-5,25)
ax.set_zlabel('Hauteur')
ax.set_zlim(0,40)

plt.show()

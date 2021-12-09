#! /usr/bin/python3
import sys
import Noyau
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

largeur = 20
hauteur = 30
longueur = 40
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

ax.set_title('Belle rivière !')

ax.set_xlabel('Longueur')
ax.set_xlim(0,40)
ax.set_ylabel('Largeur')
ax.set_ylim(-5,25)
ax.set_zlabel('Hauteur')
ax.set_zlim(0,40)

def animation_frame(i):
	#fait avancer les cases EAU

	
	#retourne les coordonnées x des cases du tableau contenant l'eau à l'instant i
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

	#ax.scatter(X_sol, Y_sol, Z_sol, c = 'brown', marker='s', s = 10, alpha=0.3)
	#ax.scatter(X_air, Y_air, Z_air, c = 'skyblue', marker='s', s = 10, alpha=0.01) #voir comment on fait la couleur de l'air avec l'héritage
	#ax.scatter(X_eau, Y_eau, Z_eau, c = 'blue', marker='s', s = 10, alpha=0.2)

	ax.scatter(X_sol, Y_sol, Z_sol, c = couleur_sol, cmap = "copper", marker='s', s = 10, alpha=0.3, vmin = 0, vmax = 100)
	ax.scatter(X_air, Y_air, Z_air, c = 'skyblue', marker='s', s = 10, alpha=0.002) #voir comment on fait la couleur de l'air avec l'héritage -> alpha = 0,001 l'air disparait
	ax.scatter(X_eau, Y_eau, Z_eau, c = couleur_eau, cmap = "Blues", marker='s', s = 10, alpha=0.2, vmin = 0, vmax = 100)
	Noyau.ecoulement(i)
	return ax;
	# ou cmap = plt.cm.get_cmap("blues", 5) le 5 est la séparation de l'échelle des couleurs
	# donc pour si on veut des séparation marquée ou tout continue et donc peut être moins flagrant l'avancée mais plus réelle l'avancée
  
#	print("sim_B")
#	return ax,
	
animation = FuncAnimation(fig, func = animation_frame, frames = np.arange(0, 10, 0.01), interval = 1000)
print("sim_C")
#remplacer les couleurs par cmap ou jsais pas quoi qu'on peut transferer dans le csv.
  # cmap = "blues"


plt.show()

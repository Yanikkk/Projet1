#! /usr/bin/python3
import sys
import Noyau
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

largeur = 2
hauteur = 5
longueur = 12

	#avec taille !!! 20,30,40 (ne marche pas au niveau de Case::setX(x) (il ne trouve pas l attribut privé
	#40,60,200
	

#initialise le tableau/environnement

Noyau.initialisation(largeur, hauteur, longueur)

# Graphe 3D

'''
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

animation = FuncAnimation(fig, func = animation_frame, frames = np.arange(0, 10, 0.01), interval = 1000, blit =False)
plt.show()
'''

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

X_sol = []
Y_sol = []
Z_sol = []
X_air = []
Y_air = []
Z_air = []
X_eau = []
Y_eau = []
Z_eau = []
#besoin de tout ça ? 

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

scatter_sol = ax.scatter(X_sol, Y_sol, Z_sol, c = couleur_sol, cmap = "copper", marker='s', s = 10, alpha=0.3, vmin = 0, vmax = 100)
scatter_air = ax.scatter(X_air, Y_air, Z_air, c = 'skyblue', marker='s', s = 10, alpha=0.002) #voir comment on fait la couleur de l'air avec l'héritage -> alpha = 0,001 l'air disparait
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

def animation_frame(i):
	#fait avancer les cases EAU
	
	Noyau.ecoulement(i)
	
	X_eau = Noyau.coord_Xeau()
	Y_eau = Noyau.coord_Yeau()
	Z_eau = Noyau.coord_Zeau()
	couleur_eau = Noyau.getCouleur_eau()
	#pas besoin je pense de couleur
	#print(couleur_eau)
	X_sol = Noyau.coord_Xsol()
	Y_sol = Noyau.coord_Ysol()
	Z_sol = Noyau.coord_Zsol()
	couleur_sol = Noyau.getCouleur_sol()
	#pas besoin je pense de couleur 

	X_air = Noyau.coord_Xair()
	Y_air = Noyau.coord_Yair()
	Z_air = Noyau.coord_Zair()
	#couleur_air = Noyau.getCouleur_air() si on fait ?
	
	scatter_eau._offsets3d = (X_eau, Y_eau, Z_eau)
	scatter_sol._offsets3d = (X_sol, Y_sol, Z_sol)
	scatter_air._offsets3d = (X_air, Y_air, Z_air)
	scatter_eau.set_array(couleur_eau)
	scatter_eau.stale = True
	scatter_sol.stale = True
	scatter_air.stale = True
	
	scatters = [scatter_sol, scatter_eau, scatter_air]
	return scatters

animation = FuncAnimation(fig, func=animation_frame, frames=np.arange(0, 10, 0.01), interval=100, blit=False)


plt.show()

'''

for i in range (0, 1000, 1):
	j= i/100
	print("ok?")
	Noyau.ecoulement(j)

'''

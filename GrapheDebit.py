#! /usr/bin/python3

import os
import csv
import numpy as np
import matplotlib.pyplot as plt
#appelle le fichier "Main.exe" et l'exécuter (cree le fichier excel etc.)
os.system("./Main.exe")


file = open('river_Data.csv', newline = '')
csvReader = csv.reader(file, delimiter = ',')
	
	
#graphe du débit

#calcule des axes
compteur = 0
axe_x = []
axe_debit = []
x = 0
for row in csvReader:
	if compteur == 0:
		compteur = compteur + 1
		continue #enlever continue et mettre elif ? une lligne en moins ???
	if compteur == 1:
		if x != row[0] and row[4] == 'EAU':
			axe_x.append(float(row[0]))
			axe_debit.append(float(row[3])*float(row[5]))
			x = row[0]

#Schéma des graphes


# Data for plotting
t = axe_x
s = axe_debit

fig, ax = plt.subplots()
ax.plot(t, s)

ax.set(xlabel='position latérale rivière', ylabel='débit',
       title='Le débit en fonction de la position')
ax.grid()

fig.savefig("debitGraph.png")
plt.show()



# test shema 3D

from mpl_toolkits.mplot3d import Axes3D

file = open('river_Data.csv', newline = '')
csvReader = csv.reader(file, delimiter = ',')

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

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


for row in csvReader:
	if row[4] == 'SOL':
		X_sol.append(float(row[0]))
		Y_sol.append(float(row[1]))
		Z_sol.append(float(row[2]))
	elif row[4] == 'AIR':
		X_air.append(float(row[0]))
		Y_air.append(float(row[1]))
		Z_air.append(float(row[2]))
	elif row[4] == 'EAU':
		X_eau.append(float(row[0]))
		Y_eau.append(float(row[1]))
		Z_eau.append(float(row[2]))
#	couleur.append(float(row[6]))


#remplacer les couleurs par cmap ou jsais pas quoi qu'on peut transferer dans le csv.
ax.scatter(X_sol, Y_sol, Z_sol, c = 'brown', marker='s', s = 10, alpha=0.3)
ax.scatter(X_air, Y_air, Z_air, c = 'skyblue', marker='s', s = 10, alpha=0.01)
ax.scatter(X_eau, Y_eau, Z_eau, c = "pink", marker='s', s = 10, alpha=0.2)
    # cmap = "blues"
ax.set_title('Wouahouuu ! Belle rivière !')

ax.set_xlabel('Longueur')
ax.set_xlim(0,40)
ax.set_ylabel('Largeur')
ax.set_ylim(-5,25)
ax.set_zlabel('Hauteur')
ax.set_zlim(0,40)

plt.show()




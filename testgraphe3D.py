#! /usr/bin/python3

import os
import csv
import numpy as np
import matplotlib.pyplot as plt
#appelle le fichier "Main.exe" et l'exécuter (cree le fichier excel etc.)
os.system("./Main.exe")


file = open('river_Data.csv', newline = '')
csvReader = csv.reader(file, delimiter = ',')
	

# test shema 3D

from mpl_toolkits.mplot3d import Axes3D

file = open('river_Data.csv', newline = '')
csvReader = csv.reader(file, delimiter = ',')

fig = plt.figure()
ax = fig.add_subplot(1111, projection='3d')

X_sol = []
Y_sol = []
Z_sol = []
X_air = []
Y_air = []
Z_air = []
X_eau = []
Y_eau = []
Z_eau = []


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

#remplacer les couleurs par cmap ou jsais pas quoi qu'on peut transferer dans le csv.
ax.scatter(X_sol, Y_sol, Z_sol, c = 'brown', marker='s', s = 10, alpha=0.3)
ax.scatter(X_air, Y_air, Z_air, c = 'skyblue', marker='s', s = 10, alpha=0.05)
ax.scatter(X_eau, Y_eau, Z_eau, c = 'blue', marker='s', s = 10, alpha=0.2)
    
ax.set_title('Rivière')


limite = max(X_sol) 
if limite < max(Y_sol):
	limite = max(Y_sol)
if limite <  max(Z_sol):
	limite = max(Z_sol)


ax.set_xlabel('Longueur')
ax.set_xlim(0,40)
ax.set_ylabel('Largeur')
ax.set_ylim(-5,25)
ax.set_zlabel('Hauteur')
ax.set_zlim(0,40)


plt.show()




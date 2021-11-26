#! /usr/bin/python3
import os
import csv
import numpy as np
import matplotlib.pyplot as plt
#appelle le fichier "Main.exe" et l'exécuter (crée le fichier excel etc.)
os.system("Main.exe")






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
		continue
	if compteur == 1:
		if x != row[0] and row[4] == 'EAU':
			axe_x.append(float(row[0]))
			axe_debit.append(float(row[3])*float(row[5]))
			x = row[0]
			

print(axe_x)
print(axe_debit)

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

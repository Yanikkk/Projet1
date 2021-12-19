#! /usr/bin/python3
import sys
import Noyau
import keyboard
import time
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches
from matplotlib.animation import FuncAnimation, writers
from mpl_toolkits.mplot3d import Axes3D

largeur = 20
hauteur = 30
longueur = 40

''' initialise le tableau/environnement '''
Noyau.initialisation(largeur, hauteur, longueur)

''' PREMIER GRAPHIQUE '''
fig = plt.figure(1)
plt.gcf().subplots_adjust(left = 0.03, bottom = 0.2, right = 0.90, top = 1.0, wspace = 0.3, hspace = 0)
ax = fig.add_subplot(121, projection='3d')

ax.set_title('Rivière')
ax.set_xlabel('Longueur')
ax.set_xlim(0,40)
ax.set_ylabel('Largeur')
ax.set_ylim(-5,25)
ax.set_zlabel('Hauteur')
ax.set_zlim(0,40)
pause_patch = mpatches.Patch(color='black', label='Espace = Arrêt/Marche ;')
up_down__patch = mpatches.Patch(color='black', label='up ↑ = augmente la taille des cases ;\ndown ↓ = diminue la taille des cases ;')
meteo_patch = mpatches.Patch(color='black', label='Changer la météo :  j = jour (par défaut) ; n = nuit ; b = brouillard ; \np = pluie ; r = sunrise ; t = sunset ; w = rainbow ;')
polluant_patch = mpatches.Patch(color='black', label='1 = ajoute fer ;  2 = ajoute ammoniac ;  3 = ajoute phosphore ;')
csv_patch = mpatches.Patch(color='black', label= "c = relever les polluants présents à l'instant ;")
ax.legend(handles=[pause_patch, up_down__patch, meteo_patch, polluant_patch, csv_patch],
handleheight =0.01, handlelength = 1.0, loc ='lower left', bbox_to_anchor=(0.0, -0.6), facecolor='skyblue', edgecolor='black', fontsize = 8)

X_eau_pure = np.array(Noyau.coord_X("EAU", "NO_POLLUANT"))
Y_eau_pure = np.array(Noyau.coord_Y("EAU", "NO_POLLUANT"))
Z_eau_pure = np.array(Noyau.coord_Z("EAU", "NO_POLLUANT"))
couleur_eau_pure = np.array(Noyau.getCouleur_eau("EAU", "NO_POLLUANT"))

X_eau_fer = np.array(Noyau.coord_X("EAU_POLLUE", "fer"))
Y_eau_fer = np.array(Noyau.coord_Y("EAU_POLLUE", "fer"))
Z_eau_fer = np.array(Noyau.coord_Z("EAU_POLLUE", "fer"))
couleur_eau_fer = np.array(Noyau.getCouleur_eau("EAU_POLLUE", "fer"))
cmap_fer = Noyau.Cmap("fer")

X_eau_phosphore = np.array(Noyau.coord_X("EAU_POLLUE", "phosphore"))
Y_eau_phosphore = np.array(Noyau.coord_Y("EAU_POLLUE", "phosphore"))
Z_eau_phosphore = np.array(Noyau.coord_Z("EAU_POLLUE", "phosphore"))
couleur_eau_phosphore = np.array(Noyau.getCouleur_eau("EAU_POLLUE", "phosphore"))
cmap_phosphore = Noyau.Cmap("phosphore")

X_eau_ammoniac = np.array(Noyau.coord_X("EAU_POLLUE", "ammoniac"))
Y_eau_ammoniac = np.array(Noyau.coord_Y("EAU_POLLUE", "ammoniac"))
Z_eau_ammoniac = np.array(Noyau.coord_Z("EAU_POLLUE", "ammoniac"))
couleur_eau_ammoniac = np.array(Noyau.getCouleur_eau("EAU_POLLUE", "ammoniac"))
cmap_ammoniac = Noyau.Cmap("ammoniac")

X_sol = np.array(Noyau.coord_X("SOL", "NO_POLLUANT"))
Y_sol = np.array(Noyau.coord_Y("SOL", "NO_POLLUANT"))
Z_sol = np.array(Noyau.coord_Z("SOL", "NO_POLLUANT"))
couleur_sol = np.array(Noyau.getCouleur("SOL"))

X_air = np.array(Noyau.coord_X("AIR", "NO_POLLUANT"))
Y_air = np.array(Noyau.coord_Y("AIR", "NO_POLLUANT"))
Z_air = np.array(Noyau.coord_Z("AIR", "NO_POLLUANT"))
couleur_air = np.array(Noyau.getCouleur("AIR"))

size_case = 10
s_eau_pure = []
for i in range(len(X_eau_pure)) :
	s_eau_pure.append(size_case)
S_eau_pure = np.array(s_eau_pure)
s_eau_pure.clear()

s_eau_fer = []
for i in range(len(X_eau_fer)) :
	s_eau_fer.append(size_case)
S_eau_fer = np.array(s_eau_fer)
s_eau_fer.clear()

s_eau_phosphore = []
for i in range(len(X_eau_phosphore)) :
	s_eau_phosphore.append(size_case)
S_eau_phosphore = np.array(s_eau_phosphore)
s_eau_phosphore.clear()

s_eau_ammoniac = []
for i in range(len(X_eau_ammoniac)) :
	s_eau_ammoniac.append(size_case)
S_eau_ammoniac = np.array(s_eau_ammoniac)
s_eau_ammoniac.clear()

s_sol = []
for i in range(len(X_sol)) :
	s_sol.append(size_case)
S_sol = np.array(s_sol)
s_sol.clear()

s_air = []
for i in range(len(X_air)) :
	s_air.append(size_case)
S_air = np.array(s_air)
s_air.clear()

scatter_sol = ax.scatter(X_sol, Y_sol, Z_sol, c = couleur_sol, cmap = "copper", marker='s', s = S_sol, alpha=0.3, vmin = 0, vmax = 100)
scatter_air = ax.scatter(X_air, Y_air, Z_air, c = couleur_air, cmap = "jet", marker='s', s = S_air, alpha=0.005, vmin = 0, vmax = 100) 
scatter_eau_pure = ax.scatter(X_eau_pure, Y_eau_pure, Z_eau_pure, c = couleur_eau_pure, cmap = "Blues", marker='s', s = S_eau_pure, alpha=0.2, vmin = 0, vmax = 100)
scatter_eau_fer = ax.scatter(X_eau_fer, Y_eau_fer, Z_eau_fer, c = couleur_eau_fer, cmap = cmap_fer, marker='s', s = S_eau_fer, alpha=0.6, vmin = 0, vmax = 100)
scatter_eau_phosphore = ax.scatter(X_eau_phosphore, Y_eau_phosphore, Z_eau_phosphore, c = couleur_eau_phosphore, cmap = cmap_phosphore, marker='s', s = S_eau_phosphore, alpha=0.6, vmin = 0, vmax = 100)
scatter_eau_ammoniac = ax.scatter(X_eau_ammoniac, Y_eau_ammoniac, Z_eau_ammoniac, c = couleur_eau_ammoniac, cmap = cmap_ammoniac, marker='s', s = S_eau_ammoniac, alpha=0.6, vmin = 0, vmax = 100)

''' DEUXIEME GRAPHIQUE '''

ax2 = fig.add_subplot(122, projection='3d')
ax2.set_title('Polluant')
ax2.set_xlabel('Longueur')
ax2.set_xlim(0,40)
ax2.set_ylabel('Largeur')
ax2.set_ylim(-5,25)
ax2.set_zlabel('Hauteur')
ax2.set_zlim(0,40)
red_patch = mpatches.Patch(color='red', label='Fer')
green_patch = mpatches.Patch(color='green', label='Phosphore')
orange_patch = mpatches.Patch(color='orange', label='Ammoniac')
ax2.legend(handles=[red_patch, green_patch, orange_patch], facecolor='skyblue', edgecolor='blue', handlelength =0.7)

scatter_eau_fer_bis = ax2.scatter(X_eau_fer, Y_eau_fer, Z_eau_fer, c = couleur_eau_fer, cmap = cmap_fer, marker='s', s = S_eau_fer, alpha=0.35, vmin = 0, vmax = 100)
scatter_eau_phosphore_bis = ax2.scatter(X_eau_phosphore, Y_eau_phosphore, Z_eau_phosphore, c = couleur_eau_phosphore, cmap = cmap_phosphore, marker='s', s = S_eau_phosphore, alpha=0.35, vmin = 0, vmax = 100)
scatter_eau_ammoniac_bis = ax2.scatter(X_eau_ammoniac, Y_eau_ammoniac, Z_eau_ammoniac, c = couleur_eau_ammoniac, cmap = cmap_ammoniac, marker='s', s = S_eau_ammoniac, alpha=0.35, vmin = 0, vmax = 100)

def change_meteo():
	if keyboard.is_pressed('j'): #jour (par défaut)
		print("Il fait jour")
		for i in range(len(couleur_air)):
			couleur_air[i] = 35
	if keyboard.is_pressed('p'): #pluie
		print("Il pleut...")
		for i in range(len(couleur_air)):
			couleur_air[i] = 15
	if keyboard.is_pressed('b'): #brouillard 
		print("Il y a du brouillard")
		for i in range(len(couleur_air)):
			couleur_air[i] = 100
	if keyboard.is_pressed('n'): #nuit
		print("Il fait nuit !")
		for i in range(len(couleur_air)):
			couleur_air[i] = 0
	if keyboard.is_pressed('r'): #sunrise
		print("Le Soleil se lève")
		for i in range(len(couleur_air)):
			couleur_air[i] = 90
	if keyboard.is_pressed('t'): #sunset
		print("Le Soleil de couche")
		for i in range(len(couleur_air)):
			couleur_air[i] = 75
	if keyboard.is_pressed('w'): #arc-en-ciel
		print("Wouahh un arc-en-ciel !")
		palier = len(couleur_air)/100
		j = 0
		compteur = 0
		for i in range(len(couleur_air)):
			if compteur > palier :
				compteur = 0
				j += 1
			compteur += 1
			couleur_air[i] = j

def change_taille():
	global size_case
	if keyboard.is_pressed('up') :
		if size_case < 5 :
			size_case += 1
		else : 
			size_case += 5
		print("La taille des cases est maintenant de " + str(size_case))
		for i in range(len(S_sol)) :
			S_sol[i] = size_case
		for i in range(len(S_eau_pure)) :
			S_eau_pure[i] = size_case
		for i in range(len(S_eau_fer)) :
			S_eau_fer[i] = size_case	
		for i in range(len(S_eau_phosphore)) :
			S_eau_phosphore[i] = size_case
		for i in range(len(S_eau_ammoniac)) :
			S_eau_ammoniac[i] = size_case	
		for i in range(len(S_air)) :
			S_air[i] = size_case
		time.sleep(0.1)
		
	if keyboard.is_pressed('down') and size_case > 1 :
		if size_case <= 5 : 
			size_case -= 1
		else :
			size_case -= 5
		print("La taille des cases est maintenant de " + str(size_case))	
		for i in range(len(S_sol)) :
			S_sol[i] = size_case
		for i in range(len(S_eau_pure)) :
			S_eau_pure[i] = size_case
		for i in range(len(S_eau_fer)) :
			S_eau_fer[i] = size_case
		for i in range(len(S_eau_phosphore)) :
			S_eau_phosphore[i] = size_case
		for i in range(len(S_eau_ammoniac)) :
			S_eau_ammoniac[i] = size_case
		for i in range(len(S_air)) :
			S_air[i] = size_case
		time.sleep(0.1)

compteur_csv = 1

def animation_frame(i):
	''' fait avancer les cases EAU '''

	if keyboard.is_pressed('space'):
		print("Arrêt")
		keyboard.wait('space')
		print("Marche")
		time.sleep(0.1)
	
	if keyboard.is_pressed('c'):
		global compteur_csv
		filename = "data_pollution" + str(compteur_csv) + ".csv"
		Noyau.writeCsv(filename)
		compteur_csv += 1
		time.sleep(0.1)
	
	if keyboard.is_pressed('1'):
		print("Fer ajouté !")
		Noyau.pollution(1)
		time.sleep(0.15)
	if keyboard.is_pressed('2'):
		print("Phosphore ajouté !")
		Noyau.pollution(2)
		time.sleep(0.15)
	if keyboard.is_pressed('3'):
		print("Ammoniac ajouté !")
		Noyau.pollution(3)
		time.sleep(0.15)
	
	Noyau.ecoulement(i)
	change_meteo()
	change_taille()

	X_eau_pure = np.array(Noyau.coord_X("EAU", "NO_POLLUANT"))
	Y_eau_pure = np.array(Noyau.coord_Y("EAU", "NO_POLLUANT"))
	Z_eau_pure = np.array(Noyau.coord_Z("EAU", "NO_POLLUANT"))
	couleur_eau_pure = np.array(Noyau.getCouleur_eau("EAU", "NO_POLLUANT")) #on verra la couleur
	
	X_eau_fer = np.array(Noyau.coord_X("EAU_POLLUE", "fer"))
	Y_eau_fer = np.array(Noyau.coord_Y("EAU_POLLUE", "fer"))
	Z_eau_fer = np.array(Noyau.coord_Z("EAU_POLLUE", "fer"))
	couleur_eau_fer = np.array(Noyau.getCouleur_eau("EAU_POLLUE", "fer"))
	
	X_eau_phosphore = np.array(Noyau.coord_X("EAU_POLLUE", "phosphore"))
	Y_eau_phosphore = np.array(Noyau.coord_Y("EAU_POLLUE", "phosphore"))
	Z_eau_phosphore = np.array(Noyau.coord_Z("EAU_POLLUE", "phosphore"))
	couleur_eau_phosphore = np.array(Noyau.getCouleur_eau("EAU_POLLUE", "phosphore"))

	X_eau_ammoniac = np.array(Noyau.coord_X("EAU_POLLUE", "ammoniac"))
	Y_eau_ammoniac = np.array(Noyau.coord_Y("EAU_POLLUE", "ammoniac"))
	Z_eau_ammoniac = np.array(Noyau.coord_Z("EAU_POLLUE", "ammoniac"))
	couleur_eau_ammoniac = np.array(Noyau.getCouleur_eau("EAU_POLLUE", "ammoniac"))

	X_sol = np.array(Noyau.coord_X("SOL", "NO_POLLUANT"))
	Y_sol = np.array(Noyau.coord_Y("SOL", "NO_POLLUANT"))
	Z_sol = np.array(Noyau.coord_Z("SOL", "NO_POLLUANT"))
	couleur_sol = np.array(Noyau.getCouleur("SOL"))
	
	X_air = np.array(Noyau.coord_X("AIR", "NO_POLLUANT"))
	Y_air = np.array(Noyau.coord_Y("AIR", "NO_POLLUANT"))
	Z_air = np.array(Noyau.coord_Z("AIR", "NO_POLLUANT"))
	
	global size_case
	s_eau_pure = []
	for i in range(len(X_eau_pure)) :
		s_eau_pure.append(size_case)
	S_eau_pure = np.array(s_eau_pure)
	s_eau_pure.clear()

	s_eau_fer = []
	for i in range(len(X_eau_fer)) :
		s_eau_fer.append(size_case)
	S_eau_fer = np.array(s_eau_fer)
	s_eau_fer.clear()
	
	s_eau_phosphore = []
	for i in range(len(X_eau_phosphore)) :
		s_eau_phosphore.append(size_case)
	S_eau_phosphore = np.array(s_eau_phosphore)
	s_eau_phosphore.clear()
	
	s_eau_ammoniac = []
	for i in range(len(X_eau_ammoniac)) :
		s_eau_ammoniac.append(size_case)
	S_eau_ammoniac = np.array(s_eau_ammoniac)
	s_eau_ammoniac.clear()
	
	s_sol = []
	for i in range(len(X_sol)) :
		s_sol.append(size_case)
	S_sol = np.array(s_sol)
	s_sol.clear()

	s_air = []
	for i in range(len(X_air)) :
		s_air.append(size_case)
	S_air = np.array(s_air)
	s_air.clear()

	scatter_eau_pure._offsets3d = (X_eau_pure, Y_eau_pure, Z_eau_pure)
	scatter_eau_pure.set_array(couleur_eau_pure)
	scatter_eau_pure.set_sizes(S_eau_pure)
	
	scatter_eau_fer._offsets3d = (X_eau_fer, Y_eau_fer, Z_eau_fer)
	scatter_eau_fer.set_array(couleur_eau_fer)
	scatter_eau_fer.set_sizes(S_eau_fer)
	scatter_eau_fer_bis._offsets3d = (X_eau_fer, Y_eau_fer, Z_eau_fer)
	scatter_eau_fer_bis.set_array(couleur_eau_fer)
	scatter_eau_fer_bis.set_sizes(S_eau_fer)
	
	scatter_eau_phosphore._offsets3d = (X_eau_phosphore, Y_eau_phosphore, Z_eau_phosphore)
	scatter_eau_phosphore.set_array(couleur_eau_phosphore)
	scatter_eau_phosphore.set_sizes(S_eau_phosphore)
	scatter_eau_phosphore_bis._offsets3d = (X_eau_phosphore, Y_eau_phosphore, Z_eau_phosphore)
	scatter_eau_phosphore_bis.set_array(couleur_eau_phosphore)
	scatter_eau_phosphore_bis.set_sizes(S_eau_phosphore)
	
	scatter_eau_ammoniac._offsets3d = (X_eau_ammoniac, Y_eau_ammoniac, Z_eau_ammoniac)
	scatter_eau_ammoniac.set_array(couleur_eau_ammoniac)
	scatter_eau_ammoniac.set_sizes(S_eau_ammoniac)
	scatter_eau_ammoniac_bis._offsets3d = (X_eau_ammoniac, Y_eau_ammoniac, Z_eau_ammoniac)
	scatter_eau_ammoniac_bis.set_array(couleur_eau_ammoniac)
	scatter_eau_ammoniac_bis.set_sizes(S_eau_ammoniac)
	
	scatter_sol._offsets3d = (X_sol, Y_sol, Z_sol)
	scatter_sol.set_sizes(S_sol)
	
	scatter_air._offsets3d = (X_air, Y_air, Z_air)
	scatter_air.set_array(couleur_air)
	scatter_air.set_sizes(S_air)
	
	scatters = [scatter_sol, scatter_eau_fer, scatter_eau_fer_bis, scatter_eau_phosphore, scatter_eau_phosphore_bis,
				scatter_eau_ammoniac, scatter_eau_ammoniac_bis, scatter_eau_pure, scatter_air]

	return scatters

anim = FuncAnimation(fig, func=animation_frame, frames=np.arange(0, 10, 0.1), interval=100, blit=False)
anim2 = FuncAnimation(fig, func=animation_frame, frames=np.arange(0, 10, 0.1), interval=100, blit=False)

''' ----------------> SI ON VEUT ENREGISTRER LA SIMULATION EN gif (OU mp4 EN CHANGEANT LE .gif  EN .mp4) '''
'''
Writer = writers['ffmpeg']
writer = Writer(fps=5, metadata={'artist': 'Me'}, bitrate=1800)
anim.save('riviere_avecpolluant.gif', writer)
'''
plt.show()

print("----------------------FIN----------------------")


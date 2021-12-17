#! /usr/bin/python3
import sys
import Noyau
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import keyboard
import time

largeur = 10
hauteur = 5
longueur = 14

	#avec taille !!! 20,30,40 (ne marche pas au niveau de Case::setX(x) (il ne trouve pas l attribut privé
	#40,60,200
	
#initialise le tableau/environnement

Noyau.initialisation(largeur, hauteur, longueur)
#Noyau.pollution(1)

# Graphe 3D
from mpl_toolkits.mplot3d import Axes3D
fig = plt.figure(1)
ax = fig.add_subplot(121, projection='3d')

ax.set_title('Belle rivière !')
ax.set_xlabel('Longueur')
ax.set_xlim(0,40)
ax.set_ylabel('Largeur')
ax.set_ylim(-5,25)
ax.set_zlabel('Hauteur')
ax.set_zlim(0,40)

textstr = ' Arrêt/Marche : Espace\n\n up : augmente la taille\n des cases\n down : diminue la taille\n des cases\n\n changer la météo : \n\n j = jour (par défaut)\n n = nuit\n b = brouillard\n p = pluie\n r = sunrise\n s = sunset\n w = rainbow\n'
plt.figtext(0, 1, textstr, fontsize = 8)
#plt.grid(True)

#retourne les coordonnées x des cases du tableau contenant l'eau à l'instant i
'''
X_eau = np.array(Noyau.coord_X("EAU"))
Y_eau = np.array(Noyau.coord_Y("EAU"))
Z_eau = np.array(Noyau.coord_Z("EAU"))
couleur_eau = np.array(Noyau.getCouleur_eau())
'''
X_eau_pure = np.array(Noyau.coord_X("EAU"))
Y_eau_pure = np.array(Noyau.coord_Y("EAU"))
Z_eau_pure = np.array(Noyau.coord_Z("EAU"))
X_eau_pollue = np.array(Noyau.coord_X("EAU_POLLUE"))
Y_eau_pollue = np.array(Noyau.coord_Y("EAU_POLLUE"))
Z_eau_pollue = np.array(Noyau.coord_Z("EAU_POLLUE"))
couleur_eau_pure = np.array(Noyau.getCouleur_eau("EAU")) #on verra la couleur
couleur_eau_pollue = np.array(Noyau.getCouleur_eau("EAU_POLLUE"))

X_sol = np.array(Noyau.coord_X("SOL"))
Y_sol = np.array(Noyau.coord_Y("SOL"))
Z_sol = np.array(Noyau.coord_Z("SOL"))
couleur_sol = np.array(Noyau.getCouleur_sol())

X_air = np.array(Noyau.coord_X("AIR"))
Y_air = np.array(Noyau.coord_Y("AIR"))
Z_air = np.array(Noyau.coord_Z("AIR"))
couleur_air = np.array(Noyau.getCouleur_air())

size_case = 30
'''
s_eau_pure = []
for i in range(len(X_eau_pure)) : 
	s_eau_pure.append(size_case)
S_eau_pure = np.array(s_eau_pure)
s_eau_pure.clear()

s_eau_pollue = []
for i in range(len(X_eau_pollue)) : 
	s_eau_pollue.append(size_case)
S_eau_pollue = np.array(s_eau_pollue)
s_eau_pollue.clear()

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
'''
if Noyau.Cmap("fer") != 0 : 
	cmap_pollue = Noyau.Cmap("fer")
else :
	cmap_pollue = "Greys"

scatter_sol = ax.scatter(X_sol, Y_sol, Z_sol, c = couleur_sol, cmap = "copper", marker='s', s = size_case, alpha=0.3, vmin = 0, vmax = 100)
scatter_air = ax.scatter(X_air, Y_air, Z_air, c = couleur_air, cmap = "jet", marker='s', s = size_case, alpha=0.005, vmin = 0, vmax = 100) #voir comment on fait la couleur de l'air avec l'héritage -> alpha = 0,001 l'air disparait
#scatter_eau = ax.scatter(X_eau, Y_eau, Z_eau, c = couleur_eau, cmap = "Blues", marker='s', s = S_eau, alpha=0.2, vmin = 0, vmax = 100)
scatter_eau_pure = ax.scatter(X_eau_pure, Y_eau_pure, Z_eau_pure, c = couleur_eau_pure, cmap = "Blues", marker='s', s = size_case, alpha=0.2, vmin = 0, vmax = 100)
scatter_eau_pollue = ax.scatter(X_eau_pollue, Y_eau_pollue, Z_eau_pollue, c = couleur_eau_pollue, cmap = cmap_pollue, marker='s', s = size_case, alpha=0.2, vmin = 0, vmax = 100)

def change_meteo():
	if keyboard.is_pressed('j'): #jour (de base)
		for i in range(len(couleur_air)): 
			couleur_air[i] = 35 
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


def change_taille():
	global size_case
	if keyboard.is_pressed('up') : 
		size_case += 10
		'''
		for i in range(len(S_sol)) : 
			S_sol[i] = size_case 
		for i in range(len(S_eau_pure)) : 
			S_eau_pure[i] = size_case 
		for i in range(len(S_eau_pollue)) : 
			S_eau_pollue[i] = size_case 
		for i in range(len(S_air)) : 
			S_air[i] = size_case 
		'''
		time.sleep(0.1)	
	if keyboard.is_pressed('down') and size_case > 10 : 
		size_case -= 10
		'''
		for i in range(len(S_sol)) : 
			S_sol[i] = size_case
		for i in range(len(S_eau_pure)) : 
			S_eau_pure[i] = size_case
		for i in range(len(S_eau_pollue)) : 
			S_eau_pollue[i] = size_case
		for i in range(len(S_air)) : 
			S_air[i] = size_case
		'''
		time.sleep(0.1)
	

#test avec le fer

'''
#pour pause -> enleve si on garde space
	#décale tout animation_frame dans cette fonction
	def run_animation():
		anim_running = True

		def onClick(event):
			nonlocal anim_running
			if anim_running:
				anim.event_source.stop()
				anim_running = False
			else:
				anim.event_source.start()
				anim_running = True
'''

def animation_frame(i):
	#fait avancer les cases EAU
	
	if keyboard.is_pressed('space'):
		keyboard.wait('space')
		time.sleep(0.1)
	
	'''
	if pollution_state == 1:
		Noyau.pollution(pollution_state)
		pollution_state = 0
	'''

	Noyau.ecoulement(i)
	change_meteo()
	change_taille()
	X_eau_pure = np.array(Noyau.coord_X("EAU"))
	Y_eau_pure = np.array(Noyau.coord_Y("EAU"))
	Z_eau_pure = np.array(Noyau.coord_Z("EAU"))
	X_eau_pollue = np.array(Noyau.coord_X("EAU_POLLUE"))
	Y_eau_pollue = np.array(Noyau.coord_Y("EAU_POLLUE"))
	Z_eau_pollue = np.array(Noyau.coord_Z("EAU_POLLUE"))
	couleur_eau_pure = np.array(Noyau.getCouleur_eau("EAU")) #on verra la couleur
	couleur_eau_pollue = np.array(Noyau.getCouleur_eau("EAU_POLLUE"))
	X_sol = np.array(Noyau.coord_X("SOL"))
	Y_sol = np.array(Noyau.coord_Y("SOL"))
	Z_sol = np.array(Noyau.coord_Z("SOL"))
	couleur_sol = np.array(Noyau.getCouleur_sol())
	X_air = np.array(Noyau.coord_X("AIR"))
	Y_air = np.array(Noyau.coord_Y("AIR"))
	Z_air = np.array(Noyau.coord_Z("AIR"))
	#couleur_air = Noyau.getCouleur_air() 
	#scatter_eau._offsets3d = (X_eau, Y_eau, Z_eau)
	scatter_eau_pure._offsets3d = (X_eau_pure, Y_eau_pure, Z_eau_pure)
	#scatter_eau_pollue._offsets3d = (X_eau_pollue, Y_eau_pollue, Z_eau_pollue)
	scatter_sol._offsets3d = (X_sol, Y_sol, Z_sol)
	scatter_air._offsets3d = (X_air, Y_air, Z_air)
	scatter_eau_pure.set_array(couleur_eau_pure)
	#scatter_eau_pollue.set_array(couleur_eau_pollue)
	scatter_air.set_array(couleur_air)
	#scatter_eau.set_sizes(S_eau)
	#scatter_eau_pure.set_sizes(S_eau_pure)
	#scatter_eau_pollue.set_sizes(S_eau_pollue)
	#scatter_air.set_sizes(S_air)
	#scatter_sol.set_sizes(S_sol)
	#if Noyau.Cmap("fer") != 0 : 
	scatter_eau_pollue._offsets3d = (X_eau_pollue, Y_eau_pollue, Z_eau_pollue)
	scatter_eau_pollue.set_array(couleur_eau_pollue)
	scatter_eau_pollue_bis._offsets3d = (X_eau_pollue, Y_eau_pollue, Z_eau_pollue)
	scatter_eau_pollue_bis.set_array(couleur_eau_pollue)
	#scatter_eau_pollue.set_sizes(S_eau_pollue)
	'''
	scatter_eau.stale = True
	scatter_sol.stale = True
	scatter_air.stale = True
	'''
	#if Noyau.Cmap("fer") != 0 :
	scatters = [scatter_sol, scatter_eau_pollue, scatter_eau_pure, scatter_air]
	#scatters = [scatter_sol, scatter_eau_pure, scatter_air]
	'''
	print("----DD-----")
	print(X_eau_pollue)
	print(len(X_eau_pollue))
	print(Y_eau_pollue)
	print(len(Y_eau_pollue))
	print(Z_eau_pollue)
	print(len(Z_eau_pollue))
	print(len(couleur_eau_pollue))
	#print(len(S_eau_pollue))
	print("---------")
	print(X_eau_pure) 
	print(len(X_eau_pure))
	print(Y_eau_pure) 
	print(len(Y_eau_pure))
	print(Z_eau_pure) 
	print(len(Z_eau_pure))
	print(len(couleur_eau_pure))
	#print(len(S_eau_pure))
	print("----DD----")
	'''
	
	return scatters
	'''
	#pour pause -> enlever si on garde l'espace
	fig.canvas.mpl_connect('button_press_event', onClick)
	'''
anim = FuncAnimation(fig, func=animation_frame, frames=np.arange(0, 10, 0.01), interval=100, blit=False)

#tester si juste ça ça passe déjà
#FFwriter = animation.FFMpegWriter()
#anim.save('animation.mp4', writer = FFwriter, fps=10)

#plt.show()

'''
DEUXIEME GRAPHIQUE
'''

fig2 = plt.figure(1)
ax2 = fig2.add_subplot(122, projection='3d')
ax2.set_title('Beau Polluant !')
ax2.set_xlabel('Longueur')
ax2.set_xlim(0,40)
ax2.set_ylabel('Largeur')
ax2.set_ylim(-5,25)
ax2.set_zlabel('Hauteur')
ax2.set_zlim(0,40)

if Noyau.Cmap("fer") != 0 :
	cmap_pollue = Noyau.Cmap("fer")
else :
	cmap_pollue = "Greys"

scatter_eau_pollue_bis = ax2.scatter(X_eau_pollue, Y_eau_pollue, Z_eau_pollue, c = couleur_eau_pollue, cmap = cmap_pollue, marker='s', s = size_case, alpha=0.2, vmin = 0, vmax = 100)

anim2 = FuncAnimation(fig2, func=animation_frame, frames=np.arange(0, 10, 0.01), interval=100, blit=False)

plt.show()









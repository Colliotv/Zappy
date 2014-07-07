import os, sys
import socket
from iaClass import *
from actions import *

def findResources(ia, obj):
	ia.voir()
	i = 0;
	for fullCase in ia.listVoir:
		splitCase = fullCase.split(' ')
		for item in splitCase:
			if (item == obj):
				if (i == 0):
					ia.prend(obj)
					print("PRIS")
					return 1
				if (i == 1):
					ia.avance()
					ia.gauche()
					ia.avance()
					ia.prend(obj)
					print("PRIS")
					return 1
				if (i == 2):
					ia.avance()
					ia.prend(obj)
					print("PRIS")
					return 1
				if (i == 3):
					ia.avance()
					ia.droite()
					ia.avance()
					ia.prend(obj)
					print("PRIS")
					return 1
				if (i == 4):
					ia.avance()
					ia.avance()
					ia.gauche()
					ia.avance()
					ia.avance()
					ia.prend(obj)
					print("PRIS")
					return 1
				if (i == 5):
					ia.avance()
					ia.avance()
					ia.gauche()
					ia.avance()
					ia.prend(obj)
					print("PRIS")
					return 1
				if (i == 6):
					ia.avance()
					ia.avance()
					ia.prend(obj)
					print("PRIS")
					return 1
				if (i == 7):
					ia.avance()
					ia.avance()
					ia.droite()
					ia.avance()
					ia.prend(obj)
					print("PRIS")
					return 1
				if (i == 8):
					ia.avance()
					ia.avance()
					ia.droite()
					ia.avance()
					ia.avance()
					ia.prend(obj)
					print("PRIS")
					return 1
		i = i + 1
	ia.avance()
	return -1

def getCloser(ia, position):
	pos = position
	print("pos =", pos)
	if (pos == 0):
		ia.reached = 1
		return 1
	if (2 <= pos <= 4):
		ia.gauche()
		ia.avance()
		print("gauche avance")
		if pos == 2:
			ia.droite()
			ia.avance()
			print("droite avance")
		elif pos == 4:
			ia.gauche()
			ia.avance()
			print("gauche avance")
	elif (6 <= pos <= 8):
		ia.droite()
		ia.avance()
		print("droite avance")
		if pos == 6:
			ia.droite()
			ia.avance()
			print("droite avance")
		elif pos == 8:
			ia.gauche()
			ia.avance()
			print("gauche avance")
	else:
		if (pos == 1):
			ia.avance()
			print("avance")
		else:
			ia.droite()
			ia.droite()
			ia.avance()
			print("droite droite avance")

	return 0

def checkNourriture(ia):
	ia.inventaire()
	lfood = ia.listInventaire[0]
	ia.food = int(lfood[12:len(lfood)])
	if ia.food < 10:
		return -1
	else:
		return 0

def nbPlayerOnCase(ia):
	ia.voir()
	i = 0
	nbPlayer = 0
	ia.listVoir = ia.listVoir[0].split(' ')
	lenList = len(ia.listVoir)
	while i != lenList:
		if ia.listVoir[i] == "joueur":
			nbPlayer += 1
		i += 1
	return nbPlayer


def checkInventaire(ia):
	ia.inventaire()
	linemate = 0
	deraumere = 0
	sibur = 0
	mendiane = 0
	phiras = 0
	thystame = 0
	i = 1
	while i != len(ia.dictionnaireLvl[ia.lvl]):
		if ia.dictionnaireLvl[ia.lvl][i] == "linemate":
			linemate += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "deraumere":
			deraumere += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "sibur":
			sibur += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "mendiane":
			mendiane += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "phiras":
			phiras += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "thystame":
			thystame += 1
		i += 1
	if ia.linemate >= linemate and ia.deraumere >= deraumere and ia.sibur >= sibur and ia.mendiane >= mendiane and ia.phiras >= phiras and ia.thystame >= thystame:
		return 0
	return -1

def takeAll(ia):
	ia.prend("nourriture")
	ia.prend("linemate")
	ia.prend("deraumere")
	ia.prend("sibur")
	ia.prend("mendiane")
	ia.prend("phiras")
	ia.prend("thystame")

def emptyCase(ia):
	while ia.listVoir[0] != "{ joueur":
		ia.voir()
		takeAll(ia)
	return 0

def poseObjet(ia):
	i = 1
	while i != len(ia.dictionnaireLvl[ia.lvl]):
		ia.pose(ia.dictionnaireLvl[ia.lvl][i])
		i += 1

def checkIncantation(ia):
	i = 1
	checkCalled(ia)
	if checkInventaire(ia) == 0:
		if nbPlayerOnCase(ia) == int(ia.dictionnaireLvl[ia.lvl][0]):
			if (checkNourriture(ia) == -1):
				while ia.food < 20:
					checkNourriture(ia)
					findResources(ia, "nourriture")
			emptyCase(ia)
			poseObjet(ia)
			ia.incantation()
			print(ia.lvl)
		else:
			print(ia.lvl)
			callOthers(ia)
			checkIncantation(ia)

	else:
		while i != len(ia.dictionnaireLvl[ia.lvl]):
			findResources(ia, ia.dictionnaireLvl[ia.lvl][i])
			i += 1
		checkIncantation(ia)


def algo(ia):
	up = 1
	while (up != 2):
		if checkNourriture(ia) == -1:
			while ia.food < 20:
				checkNourriture(ia)
				findResources(ia, "nourriture")
		ia.reached = 0
		checkIncantation(ia)
	return 0

def checkCalled(ia):
	while ia.reached != 1:
		ia.inventaire()
		for msg in ia.listMsgRecv:
			if msg[:8] == "message ":
				if msg[10:14] == "stop" and int(msg[15]) == ia.lvl:
					case = int(msg[8])
					print("ICI")
					getCloser(ia, case)
					ia.listMsgRecv.remove(msg)
					if checkNourriture(ia) == -1:
						while ia.food < 10:
							checkNourriture(ia)
							findResources(ia, "nourriture")
		print("BOUCLE")

	return -1
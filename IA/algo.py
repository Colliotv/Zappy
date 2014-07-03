import os, sys
import socket
from iaClass import *

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
	pos = int(position)
	if (pos == 0):
		return 1
	if (2 <= pos <= 4):
		print("la")
		ia.gauche()
		ia.avance()
		if pos == 2:
			ia.droite()
			ia.avance()
		elif pos == 4:
			ia.gauche()
			ia.avance()
	elif (6 <= pos <= 8):
		ia.droite()
		ia.avance()
		if pos == 6:
			ia.droite()
			ia.avance()
		elif pos == 8:
			ia.gauche()
			ia.avance()
	else:
		if (pos == 1):
			ia.avance()
		else:
			ia.droite()
			ia.droite()
			ia.avance()
	return 0

def checkNourriture(ia):
	ia.inventaire()
	lfood = ia.listInventaire[0]
	ia.food = int(lfood[12:len(lfood)])
	if ia.food < 5:
		return -1
	else:
		return 0

def checkIncantation(ia):
	return -1

def algo(ia):
	up = 1
	while (up != 2):
		ia.inventaire()
		if checkNourriture(ia) == -1:
			while ia.food < 10:
				checkNourriture(ia)
				findResources(ia, "nourriture")
		#if checkIncatation(ia) == 0:
		#	ia.incantation()
		checkCalled(ia)
		while ia.mode == "search":
			if findResources(ia, "linemate") == 1:
				ia.mode = "findOther"
	return 0

def checkCalled(ia):
	for msg in ia.listMsgRecv:
		if msg[:8] == "message ":
			print(msg[8])
			if msg[10:14] == "stop" and int(msg[15]) == ia.lvl:
				ia.mode = "comming"
				while getCloser(ia, msg[8]) != 1:
					ia.inventaire()
					if checkNourriture(ia) == -1:
						while ia.food < 10:
							checkNourriture(ia)
							findResources(ia, "nourriture")
	return -1
#!/usr/bin/python3.4

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
					print("PRIS ", obj)
					return 1
				if (i == 1):
					ia.avance()
					ia.gauche()
					ia.avance()
					ia.prend(obj)
					print("PRIS ", obj)
					return 1
				if (i == 2):
					ia.avance()
					ia.prend(obj)
					print("PRIS ", obj)
					return 1
				if (i == 3):
					ia.avance()
					ia.droite()
					ia.avance()
					ia.prend(obj)
					print("PRIS ", obj)
					return 1
				if (i == 4):
					ia.avance()
					ia.avance()
					ia.gauche()
					ia.avance()
					ia.avance()
					ia.prend(obj)
					print("PRIS ", obj)
					return 1
				if (i == 5):
					ia.avance()
					ia.avance()
					ia.gauche()
					ia.avance()
					ia.prend(obj)
					print("PRIS ", obj)
					return 1
				if (i == 6):
					ia.avance()
					ia.avance()
					ia.prend(obj)
					print("PRIS ", obj)
					return 1
				if (i == 7):
					ia.avance()
					ia.avance()
					ia.droite()
					ia.avance()
					ia.prend(obj)
					print("PRIS ", obj)
					return 1
				if (i == 8):
					ia.avance()
					ia.avance()
					ia.droite()
					ia.avance()
					ia.avance()
					ia.prend(obj)
					print("PRIS ", obj)
					return 1
		i = i + 1
	ia.avance()
	return -1

def checkFood(ia):
	ia.inventaire()
	lfood = ia.listInventaire[0]
	ia.food = int(lfood[12:len(lfood)])
	if ia.food < 10:
		return -1
	else:
		return 0

def algo(ia):
	while ia.lvl != 8:
		if checkFood(ia) == -1:
			while (ia.food < 20):
				findResources("nourriture")
		if checkCalled(ia) == 0:
			getCloser(ia)
		else:
			if checkStone(ia) == 0:
				if checkNbPlayer(ia) == 0:
					incantation(ia)
				else:
					callOthers(ia)
			else:
				getStone(ia, ia.listStoneLvl)
				algo(ia)

def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		ia = iaClass()
		ia.connect(sys.argv[1], sys.argv[2], sys.argv[3])
		start(ia)

if __name__ == '__main__':
	main()
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

def cleanList(ia, i):
	while i != len(ia.listBroadcast):
		ia.listBroadcast.pop(i)
		i += 1

def checkCalled(ia):
	i = 0
	for tmp in ia.listBroadcast:
		if tmp.find("come") != -1 and int(tmp[15]) == ia.lvl:
			ia.myBroadcast = tmp
			return 0
		if tmp.find("stop") != -1 and int(tmp[15]) == ia.lvl:
			cleanList(ia, i)
			return -1
		i += 1
	return -1

def getCloser(ia):
	case = int(ia.myBroadcast[8])
	if (pos == 0):
		return 1
	if (2 <= pos <= 4):
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
	if checkCalled(ia) == 0:
		getCloser(ia)
	return 0

def callOthers(ia):
	broadcast = "broadcast come " + str(ia.lvl)
	while checkNbPlayer(ia) != 0:
		ia.sendCmd(broadcast)
	broadcast = "broadcast stop " + str(ia.lvl)
	ia.sendCmd(broadcast)
	
def algo(ia):
	while ia.lvl != 8:
		if checkFood(ia) == -1:
			while ia.food < 20:
				checkFood(ia)
				findResources("nourriture")
		if checkCalled(ia) == 0:
			getCloser(ia)
		else:
			if checkStone(ia) == 0:
				if checkNbPlayer(ia) == 0:
					incantation(ia)
				else:
					callOthers(ia)
					incantation(ia)
			else:
				getStone(ia, ia.listStoneLvl)

def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		ia = iaClass()
		ia.connect(sys.argv[1], sys.argv[2], sys.argv[3])
		start(ia)

if __name__ == '__main__':
	main()
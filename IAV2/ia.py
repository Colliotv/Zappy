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
					return 1
				if (i == 1):
					ia.sendCmd("avance")
					ia.sendCmd("gauche")
					ia.sendCmd("avance")
					ia.prend(obj)
					#print("PRIS " + obj)
					return 1
				if (i == 2):
					ia.sendCmd("avance")
					ia.prend(obj)
					#print("PRIS " + obj)
					return 1
				if (i == 3):
					ia.sendCmd("avance")
					ia.sendCmd("droite")
					ia.sendCmd("avance")
					ia.prend(obj)
					#print("PRIS " + obj)
					return 1
				if (i == 4):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.sendCmd("gauche")
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.prend(obj)
					#print("PRIS " + obj)
					return 1
				if (i == 5):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.sendCmd("gauche")
					ia.sendCmd("avance")
					ia.prend(obj)
					#print("PRIS " + obj)
					return 1
				if (i == 6):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.prend(obj)
					#print("PRIS " + obj)
					return 1
				if (i == 7):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.sendCmd("droite")
					ia.sendCmd("avance")
					ia.prend(obj)
					#print("PRIS " + obj)
					return 1
				if (i == 8):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.sendCmd("droite")
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.prend(obj)
					#print("PRIS " + obj)
					return 1
		i = i + 1
	ia.sendCmd("avance")
	return -1

def checkFood(ia):
	ia.inventaire()
	ia.food = int(ia.listInventaire[0][12:len(ia.listInventaire[0])])
	if ia.food < 10:
		return -1
	return 0


def cleanList(ia, i):
	#while i != len(ia.listBroadcast):
	#	ia.listBroadcast.pop(i)
	#	i += 1
	return 0

def checkCalled(ia):
	i = 0

	ia.voir()
	for tmp in ia.listBroadcast:
		if tmp.find("come") != -1 and int(tmp[15]) == ia.lvl:
			ia.myBroadcast = tmp
			return 0
		if tmp.find("stop") != -1 and int(tmp[15]) == ia.lvl:
			#cleanList(ia, i)
			ia.myBroadcast = ""
			ia.listBroadcast.clear()
			return -1
		i += 1
	return -1

def getCloser(ia):
	ia.voir()
	pos = int(ia.myBroadcast[8])
	#print("pos =", pos)
	if (pos == 0):
		#print("ARRRIVEEEEEE")
		# b = False
		# while b != True:
		# 	msg = ia.connexion.recv(4096).decode()
		# 	if msg.find("up mon gars") != -1:
		# 		ia.lvl += 1
		# 		b = True
		# 	elif msg.find("incantation ko") != 1:
		# 		b = True
		return 1
	if (2 <= pos <= 4):
		ia.sendCmd("gauche")
		ia.sendCmd("avance")
		#print("gauche avance")
		if pos == 2:
			ia.sendCmd("droite")
			ia.sendCmd("avance")
			#print("droite avance")
		elif pos == 4:
			ia.sendCmd("gauche")
			ia.sendCmd("avance")
			#print("gauche avance")
	elif (6 <= pos <= 8):
		ia.sendCmd("droite")
		ia.sendCmd("avance")
		#print("droite avance")
		if pos == 6:
			ia.sendCmd("droite")
			ia.sendCmd("avance")
			#print("droite avance")
		elif pos == 8:
			ia.sendCmd("gauche")
			ia.sendCmd("avance")
			#print("gauche avance")
	else:
		if (pos == 1):
			ia.voir()
			ia.inventaire()
			ia.sendCmd("avance")
			#print("avance")
		else:
			ia.sendCmd("droite")
			ia.sendCmd("droite")
			ia.sendCmd("avance")
			#print("droite droite avance")
	ia.myBroadcast = ""
	ia.listBroadcast.clear()
	if checkCalled(ia) == 0:
		ia.voir()
		getCloser(ia)
	return 1

def checkStone(ia):
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


def getStone(ia):
	i = 1
	while i != len(ia.dictionnaireLvl[ia.lvl]):
		findResources(ia, ia.dictionnaireLvl[ia.lvl][i])
		# if checkCalled(ia) == 0:
		# 	getCloser(ia)
		# 	return 0
		i += 1


def callOthers(ia):
	i = 0
	broadcast = "broadcast come " + str(ia.lvl)
	while checkNbPlayer(ia) != 0 and i != 50:
		print("J'APPELLE")
		ia.sendCmd(broadcast)
		i += 1
	i = 0
	broadcast = "broadcast stop " + str(ia.lvl)
	while i != 25:
		print("ENVOIE STOP")
		ia.sendCmd(broadcast)
		i += 1

def poseStone(ia):
	i = 1
	while i != len(ia.dictionnaireLvl[ia.lvl]):
		ia.pose(ia.dictionnaireLvl[ia.lvl][i])
		i += 1

def takeAll(ia):
	ia.prend("nourriture")
	ia.prend("linemate")
	ia.prend("deraumere")
	ia.prend("sibur")
	ia.prend("mendiane")
	ia.prend("phiras")
	ia.prend("thystame")

def emptyCase(ia):
	ia.voir()
	while 42:
		ia.voir()
		if ia.listVoir[0].find("nourriture") == -1 and ia.listVoir[0].find("linemate") == -1 and ia.listVoir[0].find("deraumere") == -1 and ia.listVoir[0].find("sibur") == -1 and ia.listVoir[0].find("mendiane") and ia.listVoir[0].find("phiras") == -1 and ia.listVoir[0].find("thystame") == -1:
			return 0
		takeAll(ia)

def checkNbPlayer(ia):
	ia.voir()
	i = 0
	nbPlayer = 0
	#ia.listVoir = ia.listVoir[0].split(' ')
	liste = ia.listVoir[0].split(' ')
	lenList = len(liste)
	while i != lenList:
		if liste[i].find("joueur") != -1:
			nbPlayer += 1
		i += 1
	if (nbPlayer == ia.listNbPlayer[ia.lvl-1]):
		return 0
	return -1

def algo(ia):
	while ia.lvl != 8:
		if checkFood(ia) == -1:
			while ia.food < 20:
				checkFood(ia)
				findResources(ia, "nourriture")
		if checkCalled(ia) == 0:
			getCloser(ia)
		else:
			if checkStone(ia) == 0:
				emptyCase(ia)
				poseStone(ia)
				if checkNbPlayer(ia) == 0:
					ia.incantation()
				else:
					if checkCalled(ia) != 0:
						callOthers(ia)
						if checkNbPlayer(ia) == 0:
							ia.incantation()
					else:
						getCloser(ia)
			else:
				getStone(ia)

def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		ia = iaClass()
		ia.connect(sys.argv[1], sys.argv[2], sys.argv[3])
		algo(ia)

if __name__ == '__main__':
	main()
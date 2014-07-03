import os, sys
import socket
from iaClass import *

def findResources(ia, obj):
	ia.voir()
	i = 0;
	for fullCase in ia.listVoir:
		splitCase = fullCase.split(' ')
		for item in splitCase:
			print(i, splitCase)
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
	int(position) = pos
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
	return 0

def lvl2(ia):
	up = 1
	mode = "search"
	while (up != 2):
		while (mode == "search"):
			if ((findResources(ia, "linemate")) == 1):
				mode = "findOther"
		ia.avance()
	return 0

def checkMsg(ia):
	for msg in ia.listMsgRecv:
		if msg[:8] == "message ":
			if msg[10:] == "stop" and msg[15] == ia.lvl:
				getCloser(ia, msg[8])

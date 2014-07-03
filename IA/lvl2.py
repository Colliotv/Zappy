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
	if (2 <= int(position) <= 4):
		ia.gauche()
		ia.avance()
		print(" 2-3-4")
	elif (6 <= int(position) <= 8):
		ia.droite()
		ia.avance()
		print(" 6-7-8")
	else:
		if (int(position) == 1):
			ia.avance()
			print("1")
		else:
			ia.droite()
			ia.droite()
			ia.avance()
			print(" 5")
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
			getCloser(ia, msg[8])

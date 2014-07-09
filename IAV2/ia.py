#!/usr/bin/python3.4

import os, sys
import socket
from iaClass import *

def checkFood(ia):
	ia.inventaire()
	lfood = ia.listInventaire[0]
	ia.food = int(lfood[12:len(lfood)])
	if ia.food < 10:
		return -1
	else:
		return 0

def algo():
	while ia.lvl != 8:
		if checkFood(ia) == -1:
			while (ia.food < 20):
				findResources("nourriture")


def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		ia = iaClass()
		ia.connect(sys.argv[1], sys.argv[2], sys.argv[3])
		start(ia)

if __name__ == '__main__':
	main()
#!/usr/bin/python3.4

import os, sys
import socket
from iaClass import *
from lvl2 import *

def checkList(ia, sizeList):
	i = 0
	while i != sizeList:
		if ia.listVoir[i].find("linemate") != -1:
			return i
		i += 1
	return -1

def findObj(ia, obj):
	ia.voir()
	direction = checkList(ia, 3)
	if direction == -1:
		ia.avance()
	if direction == 0:
		return 1
	if direction == 1:
		ia.gauche()
		ia.avance()
		ia.droite()
		ia.avance()
		lvl1(ia)
	if direction == 2:
		ia.avance()
		return 1
	if direction == 3:
		ia.droite()
		ia.avance()
		ia.gauche()
		ia.avance()
		lvl1(ia)
	return 0
	
def lvl1(ia):
	up = 0
	linemate = 0
	mvmt = 0
	while (up != 1):
		ia.voir()
		if mvmt >= 10:
			ia.droite()
			ia.avance()
			mvmt = 0
		if (findObj(ia, "linemate") == 1):
			print("trouve!")
		mvmt += 1


	return 0
	
def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		ia = iaClass()
		ia.connect(sys.argv[1], sys.argv[2])
		ia.launchGame(sys.argv[3])
		#while (ia.lvl != 8):
		#	ia.avance()
		lvl2(ia)

if __name__ == '__main__':
	main()

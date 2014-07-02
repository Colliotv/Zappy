#!/usr/bin/python3.4

import os, sys
import socket
from serv_message import *
from iaClass import *

def lvl1(connexion):
	up = 0
	linemate = 0
	while (up != 1):
		voir(connexion)
		print(listv)
	return 0
	
def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		ia = iaClass()
		ia.connect(sys.argv[1], sys.argv[2])
		ia.launchGame(sys.argv[3])
		while (ia.lvl != 8):
			ia.avance()
			print(ia.lvl)

if __name__ == '__main__':
	main()

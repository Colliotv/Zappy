#!/usr/bin/python3.4

import os, sys
import socket
from serv_message import *

def lvl1(connexion):
	up = 0
	linemate = 0
	while (up != 1):
		avance(connexion)
	return 0
	

def lunch_game(connexion, team):
	game = True
	t = 0
	while game == True:
		if (t == 0):
			connexion.send(team.encode())
			t = 1
		lvl1(connexion)
		
	

def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		connexion = connect(sys.argv[1], sys.argv[2])
		team = sys.argv[3] + '\n'
		lunch_game(connexion, team)

if __name__ == '__main__':
	main()

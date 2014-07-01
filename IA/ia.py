#!/usr/bin/python3.4

import os, sys
import socket

def connect(serv, port):
	try:
		connexion = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		connexion.connect((serv, int(port)))
	except:
		print("connexion error")
		sys.exit()
	return (connexion)

def lunch_game(connexion, team):
	game = True
	t = 0
	while game == True:
		if (t == 0):
			connexion.send(team.encode())
		
		
	

def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		connexion = connect(sys.argv[1], sys.argv[2])
		team = sys.argv[3] + '\n'
		lunch_game(connexion, team)

if __name__ == '__main__':
	main()

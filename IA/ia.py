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

def avance(connexion):
	connexion.send(b"avance\n")
	msg_recu = ""
	while (msg_recu != "ok\n"):
		msg_recu = connexion.recv(1024).decode()

def droite(connexion):
	connexion.send(b"droite\n")
	msg_recu = ""
	while (msg_recu != "ok\n"):
		msg_recu = connexion.recv(1024).decode()

def gauche(connexion):
	connexion.send(b"gauche\n")
	msg_recu = ""
	while (msg_recu != "ok\n"):
		msg_recu = connexion.recv(1024).decode()

def prend(connexion, objet):
	prend = "prend " + objet + '\n'
	connexion.send(prend.encode())
	msg_recu = ""
	while (msg_recu != "ok\n" and msg_recu != "ko\n"):
		msg_recu = connexion.recv(1024).decode()

def pose(connexion, objet):
	pose = "pose " + objet + '\n'
	connexion.send(pose.encode())
	msg_recu = ""
	while (msg_recu != "ok\n" and msg_recu != "ko\n"):
		msg_recu = connexion.recv(1024).decode()

def expulse(connexion):
	connexion.send(b"expulse\n")
	msg_recu = ""
	while (msg_recu != "ok\n" and msg_recu != "ko\n"):
		msg_recu = connexion.recv(1024).decode()

def broadcast(connexion, msg):
	broadcast = "broadcast " + msg + '\n'
	connexion.send(broadcast.encode())
	msg_recu = ""
	while (msg_recu != "ok\n"):
		msg_recu = connexion.recv(1024).decode()

def incantation(connexion):
	connexion.send("incantation\n".encode())
	msg_recu = ""
	while (msg_recu != "elevation en cours\n" and msg_recu != "ko"):
		msg_recu = connexion.recv(1024).decode()
	if (msg_recu != "ko"):
		while(msg_recu[:15] != "niveau actuel :"):
			msg_recu = connexion.recv(1024).decode()
			lvl_actuel = int(msg_recu[17:len(msg_recu)])
			return lvl_actuel
	return -1

def expulse(connexion):
	connexion.send(b"fork\n")
	msg_recu = ""
	while (msg_recu != "ok\n"):
		msg_recu = connexion.recv(1024).decode()

def lvl1(connexion):
	up = 0
	while (up != 1):
		avance(connexion)
	print("la")
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

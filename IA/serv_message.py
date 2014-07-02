#!/usr/bin/python3.4

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

def voir(connexion, listsize):
	connexion.send(b"voir\n")
	msg_recu = connexion.recv(1024).decode()
	list1 = []
	i = 0
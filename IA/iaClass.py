import os, sys
import socket
from algo import *

class iaClass:
	def __init__(self):
		self.lvl = 1
		self.listVoir = []
		self.listInventaire = []
		self.listMsgRecv = []
		self.nbMsg = 0
		self.connexion = 0
		self.mode = ""
		self.food = 10
		self.listlvl2 = [1, "linemate"]
		self.listlvl3 = [2, "linemate", "deraumere", "sibur"]
		self.listlvl4 = [2, "linemate", "linemate", "sibur", "phiras", "phiras"]
		self.listlvl5 = [4, "linemate", "deraumere", "sibur", "sibur", "phiras"]
		self.listlvl6 = [4, "linemate", "deraumere", "deraumere", "sibur", "mendiane", "mendiane", "mendiane"]
		self.listNbPlayers = [1, 2, 2, 4, 4]

	def connect(self, serv, port):
		try:
			self.connexion = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.connexion.connect((serv, int(port)))
		except:
			print("connexion error")
			sys.exit()

	def launchGame(self, team):
		game = True
		t = 0
		self.team = team + '\n'
		self.connexion.send(self.team.encode())

	def avance(self):
		self.connexion.send(b"avance\n")
		msg_recu = ""
		while (msg_recu != "ok\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
			checkMsg(self)

	def droite(self):
		self.connexion.send(b"droite\n")
		msg_recu = ""
		while (msg_recu != "ok\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
			checkMsg(self)

	def gauche(self):
		self.connexion.send(b"gauche\n")
		msg_recu = ""
		while (msg_recu != "ok\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
			checkMsg(self)

	def prend(self, objet):
		prend = "prend " + objet + '\n'
		self.connexion.send(prend.encode())
		msg_recu = ""
		while (msg_recu != "ok\n" and msg_recu != "ko\n"):
			msg_recu = self.connexion.recv(1024).decode()		
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
			checkMsg(self)
		if msg_recu == "ok\n":
			return 0
		return -1

	def pose(self, objet):
		pose = "pose " + objet + '\n'
		self.connexion.send(pose.encode())
		msg_recu = ""
		while (msg_recu != "ok\n" and msg_recu != "ko\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
			checkMsg(self)

	def expulse(self):
		self.connexion.send(b"expulse\n")
		msg_recu = ""
		while (msg_recu != "ok\n" and msg_recu != "ko\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
			checkMsg(self)


	def broadcast(self, msg):
		broadcast = "broadcast " + msg + '\n'
		self.connexion.send(broadcast.encode())
		msg_recu = ""
		while (msg_recu != "ok\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
			checkMsg(self)

	def incantation(self):
		self.connexion.send("incantation\n".encode())
		msg_recu = ""
		while (msg_recu != "elevation en cours\n" and msg_recu != "ko"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
			if (msg_recu != "ko"):
				while(msg_recu[:15] != "niveau actuel :"):
					msg_recu = self.connexion.recv(1024).decode()
					self.listMsgRecv.append(msg_recu)
					self.nbMsg += 1
					self.lvl = int(msg_recu[17:len(msg_recu)])
					return(self.lvl)
		return -1

	def expulse(self):
		self.connexion.send(b"expulse\n")
		msg_recu = ""
		while (msg_recu != "ok\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1
	
	def voir(self):
		self.connexion.send(b"voir\n")
		msg_recu = "v"
		while (msg_recu[0] != '{'):
			msg_recu = self.connexion.recv(1024).decode()
		self.listVoir = msg_recu.split(',')

	def inventaire(self):
		self.connexion.send(b"inventaire\n")
		msg_recu = "v"
		while msg_recu[0] != '{':
			msg_recu = self.connexion.recv(1024).decode()
		self.listInventaire = msg_recu.split(',')

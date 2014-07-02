import os, sys
import socket

class iaClass:
	def __init__(self):
		self.lvl = 1
		self.listVoir = []
		self.listInventaire = []
		self.listMsgRecv = []
		self.nbMsg = 0
		self.connexion = 0

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

	def droite(self):
		self.connexion.send(b"droite\n")
		msg_recu = ""
		while (msg_recu != "ok\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1

	def gauche(self):
		self.connexion.send(b"gauche\n")
		msg_recu = ""
		while (msg_recu != "ok\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1

	def prend(self, objet):
		prend = "prend " + objet + '\n'
		self.connexion.send(prend.encode())
		msg_recu = ""
		while (msg_recu != "ok\n" and msg_recu != "ko\n"):
			msg_recu = self.connexion.recv(1024).decode()		
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1

	def pose(self, objet):
		pose = "pose " + objet + '\n'
		self.connexion.send(pose.encode())
		msg_recu = ""
		while (msg_recu != "ok\n" and msg_recu != "ko\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1

	def expulse(self):
		self.connexion.send(b"expulse\n")
		msg_recu = ""
		while (msg_recu != "ok\n" and msg_recu != "ko\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1


	def broadcast(self, msg):
		broadcast = "broadcast " + msg + '\n'
		self.connexion.send(broadcast.encode())
		msg_recu = ""
		while (msg_recu != "ok\n"):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.append(msg_recu)
			self.nbMsg += 1

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
		while (msg_recu[0] != '{'):
			msg_recu = self.connexion.recv(1024).decode()
		self.listVoir = msg_recu.split(',')
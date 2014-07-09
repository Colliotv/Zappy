import os, sys
import socket

class iaClass:
	def __init__(self):
		self.connexion = 0
		self.food = 10
		listBroadcast = []
		servReturn = False
		listVoir = []

	def connect(self, serv, port, team):
		try:
			self.connexion = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.connexion.connect((serv, int(port)))
		except:
			print("Connexion Error")
			sys.exit()
		team += "\n"
		self.connexion.send(team.encode())

	def sendCmd(self, cmd):
		self.connexion.send(cmd.encode())
		self.servReturn = False
		msg = connexion.recv(4096)
		tmplist = msg.split('\n')
		for tmp in tmplist:
			if tmp == "ok" or tmp == "ko":
				self.servReturn = True
			else:
				self.listBroadcast.insert(0, tmp)
	
	def voir(self):
		self.connexion.send(b"voir\n")
		msg = self.connexion.recv(4096)
		tmplist = msg.split('\n')
		self.servReturn = False
		for tmp in tmplist:
			if tmp.find("{") != -1:
				self.listVoir = tmp.split(',')
				self.servReturn = True
			else:
				self.listBroadcast.insert(0, tmp)

	def inventaire(self):
		self.connexion.send(b"inventaire\n")
		msg = self.connexion.recv(4096)
		tmplist = msg.split('\n')
		self.servReturn = False
		for tmp in tmplist:
			if tmp.find("{") != -1:
				self.listInventaire = tmp.split(',')
				self.servReturn = True
			else:
				self.listBroadcast.insert(0, tmp)

	def incantation(self):
		self.connexion.send(b"incantation\n")
		msg = self.connexion.recv(4096)
		tmplist = msg.split('\n')
		self.servReturn = False
		for tmp in tmplist:
			if tmp == "elevation en cours":
				c = 1
			elif tmp == "ko":
				return -1
			else:
				self.listBroadcast.insert(0, tmp)
		msg = self.connexion.recv(4096)
		tmplist = msg.split('\n')
		for tmp in tmplist:
			if tmp.find("niveau actuel") != -1 and c == 1:
				self.servReturn = True
			else:
				self.listBroadcast.insert(0, tmp)

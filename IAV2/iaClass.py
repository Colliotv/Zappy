import os, sys
import socket

class iaClass:
	def __init__(self):
		self.connexion = 0
		self.food = 10
		self.listBroadcast = []
		self.servReturn = False
		self.listVoir = []
		self.myBroadcast = ""
		self.lvl = 1
		self.listlvl2 = [1, "linemate"]
		self.listlvl3 = [2, "linemate", "deraumere", "sibur"]
		self.listlvl4 = [2, "linemate", "linemate", "sibur", "phiras", "phiras"]
		self.listlvl5 = [4, "linemate", "deraumere", "sibur", "sibur", "phiras"]
		self.listlvl6 = [4, "linemate", "deraumere", "deraumere", "sibur", "mendiane", "mendiane", "mendiane"]
		self.listlvl7 = [6, "linemate", "deraumere", "deraumere", "sibur", "sibur", "sibur", "phiras"]
		self.listlvl8 = [6, "linemate", "linemate", "deraumere", "deraumere", "sibur", "sibur", "mendiane", "mendiane", "phiras", "phiras", "thystame"]
		self.dictionnaireLvl = {}
		self.listInventaire = []
		self.linemate = 0
		self.deraumere = 0
		self.sibur = 0
		self.mendiane = 0
		self.phiras = 0
		self.thystame = 0
		self.fork = 0

	def connect(self, serv, port, team):
		try:
			self.connexion = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.connexion.connect((serv, int(port)))
		except:
			print("Connexion Error")
			sys.exit()
		team += "\n"
		self.connexion.send(team.encode())
		self.dictionnaireLvl[1] = self.listlvl2
		self.dictionnaireLvl[2] = self.listlvl3
		self.dictionnaireLvl[3] = self.listlvl4
		self.dictionnaireLvl[4] = self.listlvl5
		self.dictionnaireLvl[5] = self.listlvl6
		self.dictionnaireLvl[6] = self.listlvl7
		self.dictionnaireLvl[7] = self.listlvl8
		self.listInventaire.insert(0, "{nourriture 10")

	def sendCmd(self, cmd):
		cmd += "\n"
		self.connexion.send(cmd.encode())
		self.servReturn = False
		msg = self.connexion.recv(4096).decode()
		tmplist = msg.split('\n')
		for tmp in tmplist:
			if tmp == "ok" or tmp == "ko":
				self.servReturn = True
			else:
				self.listBroadcast.insert(0, tmp)
	
	def voir(self):
		self.connexion.send(b"voir\n")
		msg = self.connexion.recv(4096).decode()
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
		msg = self.connexion.recv(4096).decode()
		tmplist = []
		tmplist = msg.split('\n')
		self.servReturn = False
		for tmp in tmplist:
			if tmp.find("{") != -1:
				self.listInventaire = tmp.split(',')
				self.linemate = int(self.listInventaire[1][8:])
				self.deraumere = int(self.listInventaire[2][10:])
				self.sibur = int(self.listInventaire[3][6:])
				self.mendiane = int(self.listInventaire[4][8:])
				self.phiras = int(self.listInventaire[5][7:])
				self.thystame = int(self.listInventaire[6][9:10])
				self.servReturn = True
			else:
				self.listBroadcast.insert(0, tmp)

	def incantation(self):
		self.connexion.send(b"incantation\n")
		msg = self.connexion.recv(4096).decode()
		tmplist = msg.split('\n')
		self.servReturn = False
		for tmp in tmplist:
			if tmp == "elevation en cours":
				c = 1
			elif tmp == "ko":
				return -1
			else:
				self.listBroadcast.insert(0, tmp)
		msg = self.connexion.recv(4096).decode()
		tmplist = msg.split('\n')
		for tmp in tmplist:
			if tmp.find("niveau actuel") != -1 and c == 1:
				self.servReturn = True
			else:
				self.listBroadcast.insert(0, tmp)
		self.lvl += 1

	def pose(self, obj):
		pose = "pose " + obj + '\n'
		self.connexion.send(pose.encode())
		msg = self.connexion.recv(4096).decode()
		tmplist = msg.split('\n')
		self.servReturn = False
		for tmp in tmplist:
			if tmp.find("ok") != -1:
				self.servReturn = True
			else:
				self.listBroadcast.insert(0, tmp)

	def prend(self, obj):
		pose = "prend " + obj + '\n'
		self.connexion.send(pose.encode())
		msg = self.connexion.recv(4096).decode()
		tmplist = msg.split('\n')
		self.servReturn = False
		for tmp in tmplist:
			if tmp.find("ok") != -1:
				self.servReturn = True
			if tmp.find("ko") != -1:
				print("PAS DE LINEMATE SUR LA CASE")
			else:
				self.listBroadcast.insert(0, tmp)
import os, sys
import socket

class iaClass:
	def __init__(self):
		self.connexion = 0

	def connect(self, serv, port, team):
		try:
			self.connexion = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.connexion.connect((serv, int(port)))
		except:
			print("Connexion Error")
			sys.exit()
		team += "\n"
		self.connexion.send(team.encode())
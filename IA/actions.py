import os, sys
import socket
from iaClass import *
from algo import *

def callOthers(ia):
	nbPlayers = 1
	i = 0
	msg = "stop " + str(ia.lvl)
	while nbPlayers != ia.dictionnaireLvl[ia.lvl][0]:
		for fullCase in ia.listVoir:
			splitCase = fullCase.split(' ')
			for item in splitCase:
				if (i == 0):
					if (item == "joueur"):
						nbPlayers += 1
			i += 1
		ia.broadcast(msg)
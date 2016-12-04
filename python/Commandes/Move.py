r'''
Ce fichier definies la taille des packets qui sont envoyés par la station de controle au Rover.
'''

class Move:
	avancer = b'a'
	reculer = b'r'
	droite = b'd'
	gauche = b'g'
    #Parameters
	cm = b'0' #00
	m = b'1' #01
	s = b'2' #10
	m = b'3' #11
    #chosen
	chosen_commande =b''
	chosen_param =b''

	def __init__(self):

    def erase(self):
        pass

    #get information def the information form the sensor with id.
    def get(self,sensor_id,information):
        pass



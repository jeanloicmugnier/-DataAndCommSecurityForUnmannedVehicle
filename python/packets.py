r'''
definies la taille des packets qui sont envoyés par la station de controle au Rover
'''
import Rover
class Packets:
    src_id=0
    src_dst = Rover.Rover.ID
    seq_number=0
    hash=b'' # hash of the command
    commande=b'' # on of the commands to send to the rover
    parametres=b''
    def __init__(self,src_id,dst_id,seq_number,commande):
        self.commande=commande
        self.src_id = src_id
        self.dst_id = dst_id
        self.seq_number = seq_number

    '''
    Every parameter is a value in the bit format b' '
src_id | dst_id    | nom de la commande | parametre  | num de seq| hash
 3bits | 3bits     | 4bits              | 12 bits    | 1 octet   | 16 octets
    '''
    def parse(self):

        bit_packet = bytearray(0)
        bit_packet.append(self.src_id)
        bit_packet.append(self.dst_id_id)
        bit_packet.append(self.seq_number)
        bit_packet.append(self.commande)
        bit_packet.append(self.hash)


import serial
import siphash
import Commandes.Command as Commands
import packets

class Interface:
    COMPORT = '/dev/ttyUSB0'
    key = 'ABCDEFGHIJKLMNOP'
    arduino=0
    seq=0
    src_id=0
    rover_id=0

    def __init__(self):
        self.arduino = serial.Serial(self.COMPORT, 115200)
        self.arduino.timeout = 1.5


    def arduino_write(self,packet):
        self.arduino.write(packet)

    '''
    Verifies if the command exist in the list of commands
    verifies the number of parameters
    if passes the verificaiton, (for now) the command is written in the arduino
    '''
    def parse_commande(self,commande):
        msg=commande.split(" ")
        com = Commands.COMMANDS.get(msg[0]) #object from associated to the string
        params = msg[1:]
        if (com==None):
            ("Command Not Found : " + com)
            return
        if(len(params) != msg.NB_PARAMS ):
            ("Wrong Number Of Arguments: " +  str(com.NB_PARAMS) +" expected, given :" + len(params) )
            return
        packets.Packets.parse(com,params)

        # if com null, wrong commande return
        # param = com.PARAMS.get(msg[1])
        # if has more params
            # get the params


    def parse_answer(self,answer):
        ack = self.arduino.readline()

    '''
    interative command line with arduino
    '''
    def loop(self):
        sequence = 0;
        while True:
            command = raw_input("Enter a command: ")
            sip = siphash.SipHash_2_4(self.key).update(command + ';' + str(sequence)).hexdigest();
            self.arduino.write(command + ';' + str(sequence) + ';' + str(sip));
            print(command + ';' + str(sequence) + ';' + str(sip));
            sequence += 1;
            if (command == 's'):
                break;
            while True:
                ack = self.arduino.readline();
                if ack != None:
                    break;
            print ack;




'''
def main():

    arduino = serial.Serial(COMPORT, 115200)
    arduino.timeout = 1.5
    while True:
        command = raw_input("Enter a command: ")
        sip = siphash.SipHash_2_4(key).update(command+';'+str(sequence)).hexdigest();
        arduino.write(command+';'+str(sequence)+';'+str(sip));
        print(command+';'+str(sequence)+';'+str(sip));
        sequence+=1;
        if (command == 's'):
            break;
        while True:
            ack = arduino.readline();
            if ack != None:
                break;
        print ack;


main()

'''

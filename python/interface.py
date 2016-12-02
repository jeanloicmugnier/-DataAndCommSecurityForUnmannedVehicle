import serial
import siphash

COMPORT = '/dev/ttyUSB0'
key = 'ABCDEFGHIJKLMNOP';

def main():
    sequence = 0;
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



import serial
import siphash

COMPORT = '/dev/ttyUSB0'
    

def main():
    arduino = serial.Serial(COMPORT, 115200)
    arduino.timeout = 1.5
    while True:
        command = raw_input("Enter a command: ")
        key = 'ABCDEFGHIJKLMNOP';
        sip = siphash.SipHash_2_4(key).update(command).hexdigest();
        arduino.write(command+';'+str(sip));
        if (command == 's'):
            break;
        
main()



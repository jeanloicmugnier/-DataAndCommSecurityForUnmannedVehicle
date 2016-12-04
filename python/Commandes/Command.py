from abc import ABCMeta, abstractmethod

class Commande:
    __metaclass__ = ABCMeta
    COMMANDS={"move":Move,
              "sync":Sync,
              "rec":Rec,
              "srec":SRec,
              "getinfo":GetInfo,
              "erase":Erase}
    PARAMS=dict()
    NB_PARAMS=0
    name=""
    id=0

    @abstractmethod
    def get_commande(self): pass
    @abstractmethod
    def get_formatted(self):pass


'''
class responsible for syncing time between Drone and Control Station
'''
class Sync(Commande):
    super.id = b'1'
    '''
    get commande param for the sync time command
    '''
    def get_commande(self):
        pass


'''
Make the rover start recording
'''
class Rec(Commande):
    super.id = b'2'
    sendor_id=""

    '''
        get commande param for the sync time command
        '''

    def get_commande(self):
        pass


    '''
    make all the sensors start recoring
    '''
    def start_all(self):
        pass

    '''
    the sensor with id equals to sensor_id start recoring
    '''

    def start_all(self,sensor_id):
        pass


'''
Make the rover stop recording
'''
class SRec(Commande):
    sensor_id=""
    super.id = b'2'

    def __init__(self):
        pass
    '''
    get commande param for the sync time command
    '''
    def get_commande(self):
        pass

'''
    TODO
    In case the Rover is in danger, we should erase all the data in it.
    go through all the log files and erase them.

'''
class Erase(Commande):
    file_id=""
    super.id=b'4'
    '''
    get commande param for erase time command
    '''
    def get_commande(self):
        pass



class GetInfo(Commande):
    super.id=b'3'
    super.PARAMS =  {"temperature":0, "pressure":1} #update with real



r'''
DONE
Move commande.
'''
class Move(Commande):
    super.NB_PARAMS = 2
    super.id =b'0'

    #Direction
    FORW = b'0'
    BACK = b'1'
    RIGHT = b'2'
    LEFT = b'3'

    # Unit
    CM = b'0'  # 00
    M = b'1'  # 01
    S = b'2'  # 10
    MIN = b'3'  # 11

    # Chosen
    chosen_commande = b''
    chosen_param = b''
    chosen_unit = b''

    super.PARAMS = {"forward":b'0',
                    "backward":b'1',
                    "right":b'2',
                    "left":b'3',
                    "cm":b'0',
                    "m":b'1',
                    "s":b'2',
                    "min":b'3'}


    def __init__(self,direciton,param,unit):
        super.__name__="move"


    def param_to_byte(self,param):
        bytes = self.PARAMS.get(param)
        if (bytes==None):
            print("Param not found:")
        else:
            return bytes





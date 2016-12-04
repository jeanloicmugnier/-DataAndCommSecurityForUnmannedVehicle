'''
this is the interface of the Rover in the Control Station.
Here are registered the state of the ROver and it's infos.
'''
class Rover:
    ID = b'1'
    sensors = [] #list of sensors
    sensors_recording=[]
    pk=0
    file_names={}



class Sensors:
    sensor_id=""
    sensor_name=""
    value_name=""
    is_rec=False

    def __init__(self):
        pass

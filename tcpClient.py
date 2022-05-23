import socket
import sys
import json
import random as rd
import time



HOST, PORT = "192.168.106.145", 9999

d = {'4': '11', '3' :'9','2': '10' }

for _ in range(10): 

    for key, val in d.items():

        data = {}
        data['site'] = key
        data['sensor'] = val
        data['water_depth'] =  str(rd.randrange(900, 950))
        json_data = json.dumps(data)
        
    

        # Create a socket (SOCK_STREAM means a TCP socket)
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((HOST, PORT))
            sock.sendall(bytes(json_data + "\n", "utf-8"))

            received = str(sock.recv(1024), "utf-8")

        print("Sent:     {}".format(data))
        print("Received: {}".format(received))
        time.sleep(1)
    time.sleep(897)
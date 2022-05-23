import socket
import sys
import json

HOST, PORT = "192.168.43.233", 9999

data = {}
data['site'] = '5'
data['sensor'] = '11'
data['water_depth'] = '237'
json_data = json.dumps(data)


# Create a socket (SOCK_STREAM means a TCP socket)
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((HOST, PORT))
    sock.sendall(bytes(json_data + "\n", "utf-8"))

    received = str(sock.recv(1024), "utf-8")

print("Sent:     {}".format(data))
print("Received: {}".format(received))
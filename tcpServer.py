import socketserver
import requests
import json

class MyTCPHandler(socketserver.BaseRequestHandler):

    def handle(self):
        self.data = self.request.recv(1024).strip()
        print("{} wrote:".format(self.client_address[0]))
        print(self.data)
        json_data = json.loads(self.data.decode('utf-8'))
        requests.post('http://ec2-54-196-182-171.compute-1.amazonaws.com/dam-information/update', json = json_data)
        self.request.sendall(self.data.upper())

if __name__ == "__main__":
    HOST, PORT = "0.0.0.0", 9999

    with socketserver.TCPServer((HOST, PORT), MyTCPHandler) as server:
        server.serve_forever()

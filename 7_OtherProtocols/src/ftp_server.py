#!/usr/bin/env python3.9

"""FTP Server implementation in python"""

import socket
import os

HOST = socket.gethostname()      # Standard loopback interface address (localhost)
FTP_PORT = 12345    # Port to listen on (non-privileged ports are > 1023)
PATH = "files/"

class FTPServer:
    """FTP Server class"""

    def __init__(self):
        """Initialize FTP Server"""

        self.file_name = ""
        self.name = ""

    def start_ftp(self):
        """Start The FTP Server"""

        print("FTP Server started!!")
        while True:
            self.data = ""
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.sock.bind((HOST, FTP_PORT))
            print("Listening for a connection on its own port....")
            self.sock.listen(5)
            conn, addr = self.sock.accept()
            self.name = conn.recv(1024).decode("utf-8")
            print("Connected to {}".format(self.name))
            self.file_name = conn.recv(1024).decode("utf-8")
            self.file_name = PATH + self.file_name
            print("filename = {}".format(self.file_name))
            opt = conn.recv(1024).decode("utf-8")
            print("COMMAND =",opt)

            if(opt=="RETR"):
                print("\nRequest to retrieve the file {}\n".format(self.file_name))
                with open(self.file_name, "r", encoding="utf-8") as fptr:
                    self.data = fptr.read()
                conn.sendall(bytes(self.data, "utf-8"))
                print("File sent successfully")

            elif(opt=="STOR"):
                print("\nRequest to store the file {}\n".format(self.file_name))
                while True:
                    x = conn.recv(1024)
                    if(len(x)<1):
                        break
                    self.data += x.decode("utf-8")

                #print("data to be stored: {}".format(self.data))
                with open(self.file_name, "w", encoding="utf-8") as fptr:
                    fptr.write(self.data)
                print("File stored successfully")

            if(opt=="LIST"):
                print("\nRequest to list the files stored in server\n")
                for x in os.listdir(PATH):
                    if(x[0] != '.'):
                        self.data += (x+'  ')

                conn.sendall(bytes(self.data, "utf-8"))
                print("File sent successfully")

            conn.close()
            self.sock.close()
            print("FTP Server still running!")

if __name__ == "__main__":
    ftp_server = FTPServer()
    ftp_server.start_ftp()

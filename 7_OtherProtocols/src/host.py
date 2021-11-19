#!/usr/bin/env python3.9

"""Host for connecting to the servers"""

import socket
from time import sleep

HOST = socket.gethostname()     # Standard loopback interface address (localhost)
FTP_PORT = 12345 


class Host:
    """Host Class for implementing connections"""

    def __init__(self):
        "Initialize The Hosts"

        self.file_name = ""
        self.name = ""

    def connect_hosts(self):
        """Connects The Hosts To Specific Servers"""

        print("Host started!!")
        self.name = input("Enter the name of the host: ")

        while True:
            self.data = ""

            print("\n")
            print("+---------------------------------------------+")
            print("|    You want to >>                           |")
            print("|    1. Request file from FTP server          |")
            print("|    2. List files in FTP server              |")
            print("|    3. Store file in FTP server              |")
            print("|    4. Exit                                  |")
            print("+---------------------------------------------+")
            choice = input("Enter Your Choice (1/2/3/4) : ")
            print("\n")
            if choice == "4":
                print("Host has been terminated!")
                break
            if choice not in "1234":
                print("Invalid choice! Reselect 1/2/3/4")
                continue

            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.sock.connect((HOST, FTP_PORT))
            self.sock.send(bytes(self.name, "utf-8"))
            if(choice in "13"):
                self.file_name = input("Enter filename : ")
            else:
                sleep(0.3)
                self.file_name = "*"
            self.sock.send(bytes(self.file_name, "utf-8"))
            sleep(0.5)

            if choice == "1":
                self.sock.send(bytes("RETR","utf-8"))
                while True:
                    x = self.sock.recv(1024)
                    if(len(x)<1):
                        break
                    self.data += x.decode("utf-8")

                print("\nThe contents of the file :") 
                print("{}\n".format(self.data))
                self.sock.close()

            if choice == "2":
                self.sock.send(bytes("LIST","utf-8"))
                while True:
                    x = self.sock.recv(1024)
                    if(len(x)<1):
                        break
                    self.data += x.decode("utf-8")

                print("\nThe file in the server are: ") 
                print("{}\n".format(self.data))
                self.sock.close()

            elif choice == "3":
                self.sock.send(bytes("STOR","utf-8"))
                self.data = input("Data to be stored: ")
                self.sock.sendall(bytes(self.data,"utf-8"))
                self.sock.close()

if __name__ == "__main__":
    host = Host()
    host.connect_hosts()

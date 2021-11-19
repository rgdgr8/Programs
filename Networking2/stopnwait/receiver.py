import socket
import sys
import time
import random

def waitRandomTime():
    x = random.randint(0, 5)
    if x <= 1:
        time.sleep(2)


def checkError(frame):
    countOnes = 0
    for ch in frame:
        if ch == '1':
            countOnes += 1
    return countOnes % 2


def Main(senderno):
    print('Initiating Receiver #', senderno)
    host = '127.0.0.1'
    f = open('rp.txt','r')
    port = int(f.read())
    f.close()

    mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print('recvr port:',port)
    mySocket.connect((host, port))

    while True:
        print()
        data = mySocket.recv(1024).decode()
        if not data or data=='q0':
            break

        print('Received from channel :', str(data))
        waitRandomTime()
        if checkError(data) == 0:
            rdata = 'ACK'
        else:
            time.sleep(2)
            rdata = 'Corrupt Data'

        print('Sending to channel :', str(rdata))
        mySocket.send(rdata.encode())

    mySocket.close()


if __name__ == '__main__':
    if len(sys.argv) > 1:
        senderno = int(sys.argv[1])
    else:
        senderno = 1
    Main(senderno)

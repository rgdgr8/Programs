import socket
import sys
import time
import random


def waitRandomtime():
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

    f = open('ws.txt','r')
    windowsize = int(f.read())
    f.close()

    expectedfno = 0

    mySocket = socket.socket()
    mySocket.connect((host, port))

    while True:
        print()
        data = mySocket.recv(1024).decode()
        if(not data or data[0]=='q'):
            break
        msg,cnt = data.split('/')

        print('Received from channel :', data)
        waitRandomtime()
        if checkError(msg) == 0 and int(cnt)==expectedfno:
            rdata = cnt
            expectedfno = (expectedfno+1)%windowsize
        else:
            rdata = '-'+cnt

        print('Sending to channel :', rdata)
        mySocket.send(rdata.encode())

    mySocket.close()


if __name__ == '__main__':
    if len(sys.argv) > 1:
        senderno = int(sys.argv[1])
    else:
        senderno = 1
    Main(senderno)

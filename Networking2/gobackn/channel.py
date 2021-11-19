import socket
import time
import random
import os
from threading import Thread


def injectRandomError(frame):
    pos = random.randint(0, len(frame)-1)
    frame = frame[:pos]+'1'+frame[pos+1:]
    return frame

class Channel():

    def __init__(self, totalsender, totalreceiver, windowsize):
        self.totalsender = totalsender
        self.senderhost = '127.0.0.1'
        self.senderport = sp
        self.senderconn = []

        self.totalreceiver = totalreceiver
        self.receiverhost = '127.0.0.1'
        self.receiverport = rp
        self.receiverconn = []

    def initSenders(self):
        senderSocket = socket.socket()
        senderSocket.bind((self.senderhost, self.senderport))
        senderSocket.listen(self.totalsender)
        for _ in range(1, self.totalsender+1):
            conn = senderSocket.accept()
            self.senderconn.append(conn)
        print('Initiated all sender connections')

    def closeSenders(self):
        for conn in self.senderconn:
            conn[0].close()
        print('Closed all sender connections')

    def initReceivers(self):
        receiverSocket = socket.socket()
        receiverSocket.bind((self.receiverhost, self.receiverport))
        receiverSocket.listen(self.totalreceiver)
        for _ in range(1, self.totalreceiver+1):
            conn = receiverSocket.accept()
            self.receiverconn.append(conn)
        print('Initiated all receiver connections')

    def closeReceivers(self):
        for conn in self.receiverconn:
            conn[0].close()
        print('Closed all receiver connections')
                
    def channelAlgo(self,i):
        while True:
            print()
            conn = self.senderconn[i]
            data = conn[0].recv(1024).decode()
            print('Received from Sender', i+1, ':', data)
            origmsg,cnt = data.split('/')
            if not origmsg or origmsg=='q0':
                return

            recvno = random.randint(0, len(self.receiverconn)-1)
            print('Sending to Receiver', recvno+1)
            rconn = self.receiverconn[recvno]
            msg = injectRandomError(origmsg)
            newdata = msg + '/' + cnt
            rconn[0].sendto(newdata.encode(), rconn[1])
                
            # received from receiver
            rdata = rconn[0].recv(1024)
            print('Received from receiver',(recvno+1),':',rdata.decode())
            print('Sending to sender',(i+1),':',rdata.decode())
            conn[0].sendto(rdata,conn[1])

    def processData(self):
        ths = [None]*len(self.senderconn)
        j = 0
        for i in range(len(self.senderconn)):
            th = Thread(target=self.channelAlgo,args=(i,))
            th.start()
            ths[j] = th
            j += 1

        for th in ths:
            th.join()


if __name__ == '__main__':
    # Main()
    sp = random.randint(2000,5000)
    rp = random.randint(5001,9000)
    f = open('sp.txt','w')
    f.write(str(sp))
    f.close()
    f = open('rp.txt','w')
    f.write(str(rp))
    f.close()

    totalsen = int(input('Enter number of senders: '))
    totalrecv = int(input('Enter number of receivers: '))
    windowsize = int(input('Enter window size: '))

    f = open('ws.txt','w')
    f.write(str(windowsize))
    f.close()

    ch = Channel(totalsen, totalrecv, windowsize)
    ch.initReceivers()
    ch.initSenders()
    ch.processData()
    ch.closeReceivers()
    ch.closeSenders()

    os.remove('sp.txt')
    os.remove('rp.txt')
    os.remove('ws.txt')

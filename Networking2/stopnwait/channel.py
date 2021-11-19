import socket
import time
import random
import os


def injectRandomError(frame):
    num = random.randint(1,max(1,len(frame)//2))

    for i in range(num):
        pos = random.randint(0, len(frame)-1)
        frame = frame[:pos]+str((int(frame[pos])+1)%2)+frame[pos+1:]
    return frame


class Channel():

    def __init__(self, totalsender, totalreceiver):
        self.totalsender = totalsender
        self.senderhost = '127.0.0.1'
        self.senderport = sp
        self.senderconn = []

        self.totalreceiver = totalreceiver
        self.receiverhost = '127.0.0.1'
        self.receiverport = rp
        self.receiverconn = []

    def initSenders(self):
        print("channel sender port:",self.senderport)
        senderSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
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
        print("channel recvr port:",self.receiverport)
        receiverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
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

    def processData(self):
        while True:
            for i in range(len(self.senderconn)):
                print()
                conn = self.senderconn[i]
                data = conn[0].recv(1024).decode()
                t1 = time.time()
                if not data or data=='q0':
                    break

                print('Received from Sender', i+1, ':', str(data))

                recvno = random.randint(0,len(self.receiverconn)-1)
                print('Sending to Receiver', recvno+1)
                rconn = self.receiverconn[recvno]
                data = injectRandomError(data)
                rconn[0].sendto(data.encode(), rconn[1])

                rdata = rconn[0].recv(1024).decode()
                print('Received from Receiver', recvno+1, ':', str(rdata))

                print('Sending to Sender', i+1)
                conn[0].send(rdata.encode())
                print('RTT=',(time.time()-t1))

                time.sleep(0.003)
                while True:
                    try:
                        filein = open('checktime.txt', "r")
                        timeout = int(filein.read())
                        break
                    except:
                        time.sleep(0.003)
                filein.close()
                #print("timeout=",timeout==1)
                while timeout == 1:
                    print()
                    data = conn[0].recv(1024).decode()
                    if not data or data=='q0':
                        print('Repeated corruption, needs better encoding')
                        break
                    print('Again Received from Sender', i+1, ':', str(data))
                    data = injectRandomError(data)
                    print('Again Sending to Receiver', recvno+1)
                    rconn[0].sendto(data.encode(), rconn[1])
                    rdata = rconn[0].recv(1024).decode()
                    print('Again Received from Receiver',
                          recvno+1, ':', str(rdata))
                    print('Again Sending to Sender', i+1)
                    conn[0].send(rdata.encode())

                    time.sleep(0.003)
                    while True:
                        try:
                            filein = open('checktime.txt', "r")
                            timeout = int(filein.read())
                            break
                        except:
                            time.sleep(0.003)
                    filein.close()
                    #os.remove('checktime.txt')
                    #print("timeout=",timeout==1)

            if data == 'q0':
                break
        
        return


if __name__ == '__main__':
    # Main()
    sp = random.randint(5001,9000)
    rp = random.randint(2000,5000)
    f = open('sp.txt','w')
    f.write(str(sp))
    f.close()
    f = open('rp.txt','w')
    f.write(str(rp))
    f.close()
    '''totalsen = 2
    print('Number of senders',totalsen)
    totalrecv = 2
    print('Number of receivers',totalrecv)

    '''
    totalsen = int(input('Enter number of senders: '))
    totalrecv = int(input('Enter number of receivers: '))

    ch = Channel(totalsen, totalrecv)
    ch.initReceivers()
    ch.initSenders()
    ch.processData()
    ch.closeReceivers()
    ch.closeSenders()

    os.remove('sp.txt')
    os.remove('rp.txt')
    os.remove('checktime.txt')

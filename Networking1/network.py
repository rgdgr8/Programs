import socket
import sys
import time
from math import sqrt
import random
import vrc
import lrc
import crc
import checksum
from threading import Thread,Condition,Lock

class Network:
    PORT = 1025
    def __init__(self,opt,timeout=1,recvBytes=1024,bits=256):
        self.recvB = recvBytes
        self.timeout = timeout
        self.bits = bits
        self.opt = opt
        Network.PORT += 1
        #random.seed(Network.PORT)

        #---fill up file data.txt with 'bits' number of random bits---#
        with open("data.txt","w") as file:
            l = ['0']*bits
            for i in range(0,bits):
                bit = random.randint(0,1)
                l[i] = str(bit)

            l = "".join(l)
            file.write(l)

    def injectError(self,word,burst=4):
        errors = random.randint(1,len(word)//burst)
        pos = []
        while errors>0:
            ind = random.randint(0,len(word)-1)
            if ind in pos:
                continue

            pos.append(ind)
            error = '0'
            if(word[ind]=='0'):
                error = '1'
            word = word[0:ind] + error + word[(ind+1):len(word)]
            if(burst<=1):
                return word
            errors -= 1
        return word

    def sender_vrc_or_crc(self,data,mysock,vrc_or_crc):
        frame = 8 #frame size for vrc and crc is 8, assuming total data bits is divisible by 8
        num = 1
        j = 0
        for i in range(frame,len(data)+1,frame):
            dataword =  data[j:i]
            j = i
            print(f"dataword{num} =",dataword)
            codeword = vrc_or_crc.sender_check(dataword)
            print(f"sender codeword{num} =",codeword)
            codeword = self.injectError(codeword)
            mysock.sendall(codeword.encode())
            response = mysock.recv(self.recvB)
            print(f"response{num} =",response.decode())
            num += 1

    def recvr_vrc_or_crc(self,sender,vrc_or_crc):
        j = 1
        while True:
            codeword = sender.recv(self.recvB) #recv method waits until sender socket closes.
            if(len(codeword)<=0):
                break

            codeword = codeword.decode()
            print(f'recver codeword{j} =',codeword)
            error = vrc_or_crc.recvr_check(codeword)
            sender.sendall(error.encode())
            j += 1

    def sender_lrc_or_checksum(self,data,mysock,lrc_or_checksum):
        frame = self.bits//4 #frame size is (total no. of bits)/4 for checksum, assuming that the total number of bits is divisible by 4
        if(lrc_or_checksum is lrc):
            frame = int(sqrt(self.bits)) #frame size is square root of the total number of bits for lrc, assuming that the total number of bits is a perfect square.
        j = 0
        words = []
        for i in range(frame,len(data)+1,frame):
            words.append(data[j:i])
            j = i

        print('grouped words:',words)
        codeword = lrc_or_checksum.sender_check(words,frame)
        print('sender codeword:',codeword)
        codeword = self.injectError(codeword) + 'x' #x appended to indicated end of frame
        mysock.sendall(codeword.encode())
        response = mysock.recv(self.recvB)
        print(f"response =",response.decode())

    def recvr_lrc_or_checksum(self,sender,lrc_or_checksum):
        frame = self.bits//4
        if(lrc_or_checksum is lrc):
            frame = int(sqrt(self.bits))
        
        codeword = ""
        try:
            while True:
                recv = sender.recv(self.recvB)
                if(len(recv)<=0 or recv[-1]==120):#120 is x, the terminating character
                    codeword += recv[:len(recv)-1].decode()
                    break
                codeword += recv.decode()
        except Exception as e:
            if(isinstance(e,socket.timeout)==False):
                print('receiver exception:',e)

        print('recver codeword:',codeword)
        error = lrc_or_checksum.recvr_check(codeword,frame)
        #print(error)
        sender.sendall(error.encode())

    def sender(self):
        time.sleep(0.3) #so that the receiver thread starts before the sender thread
        mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        mysock.connect((socket.gethostname(),Network.PORT))

        file = open("data.txt","r")
        try:
            data = file.read() #reads entire data from the file, and then makes frames of required size later
            file.close()

            if(self.opt=='1'):
                self.sender_vrc_or_crc(data,mysock,vrc)
            elif(self.opt=='2'):
                self.sender_vrc_or_crc(data,mysock,crc)
            elif(self.opt=='3'):
                self.sender_lrc_or_checksum(data,mysock,lrc)
            elif(self.opt=='4'):
                self.sender_lrc_or_checksum(data,mysock,checksum)

        finally:
            mysock.close()

    def receiver(self):
        with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
            s.bind((socket.gethostname(),Network.PORT))
            s.listen()
            sender,addr = s.accept()

        try:
            if(self.opt=='1'):
                self.recvr_vrc_or_crc(sender,vrc)
            elif(self.opt=='2'):
                self.recvr_vrc_or_crc(sender,crc)
            elif(self.opt=='3'):
                self.recvr_lrc_or_checksum(sender,lrc)
            elif(self.opt=='4'):
                self.recvr_lrc_or_checksum(sender,checksum)
        
        except Exception as e:
            print('receiver exception:',e)
        finally:
            sender.close()

while(True):
    opt = input('''
1. VRC
2. CRC
3. LRC
4. CHECKSUM
0. Exit
''').strip()
    if(opt!='1' and opt!='2' and opt!='3' and opt!='4' and opt!='0'):
        print('Invalid Input')
        continue

    if(opt=='0'):
        sys.exit(0)

    net = Network(opt,bits=16)
    st = Thread(None,net.receiver)
    ct = Thread(None,net.sender)

    st.start()
    ct.start()
    st.join()
    ct.join()

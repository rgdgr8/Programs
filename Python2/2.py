import socket
from threading import Thread

class SP:
    PORT = 12345
    def __init__(self,timeout=1,recvBytes=1024,loop=10):
        self.recvB = recvBytes
        self.timeout = timeout
        self.loop = loop
    def changePort(cls,port):
        cls.PORT = port
        
    def client(self):
        mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        mysock.connect((socket.gethostname(),SP.PORT))
        mysock.settimeout(self.timeout)#this is required so that the blocking recv() call gets timeout exception if it is not receiving and the loop can move on. The cause of the problem is the last trip of the loop, when sendall has finished and all data has been received but still the receiver goes to the final loop run and calls recv and meanwhile sender also goes ahead after sendall and calls recv and now both the threads get blocked forever.
        try:
            for loop in range(1,self.loop):
                try:
                    cmd = 'Client message {}\r\n'.format(loop).encode()
                    mysock.sendall(cmd)
                    while True:
                        data = mysock.recv(self.recvB)
                        if len(data) < 1:
                            break
                        print(data.decode(),end='')
                except:
                    pass
        finally:
            print('client end')
            mysock.close()

    def server(self):
        with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
            s.bind((socket.gethostname(),SP.PORT))
            s.listen()
            client,addr = s.accept()
            loop = 1
        try:
            while True:
                x = client.recv(self.recvB) #recv method waits until client socket closes.
                if(len(x)<=0):
                    break
                print(x.decode(),end='')
                client.sendall("Server response {}\r\n".format(loop).encode())
                loop = loop+1
        finally:
            client.close()

sp = SP()
ct = Thread(None,sp.client)
st = Thread(None,sp.server)
ct.start()
st.start()
ct.join()
st.join()
